#include "auto_upd_firmw.h"

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>

#include "file_system/src/file_system.h"
#include "utils/src/utils.h"

AutoUpdateFw::AutoUpdateFw(const char* name, const char* id, Device* device) : Node(name, id, device) {}

bool AutoUpdateFw::Init(Homie* homie) {
    Node::Init(homie);
    LoadFwSettings();
    String str_staging_status = properties_.find("staging")->second->GetValue();
    fw_settings.staging_status = str_staging_status == "true" ? true : false;
    return true;
}

void AutoUpdateFw::HandleCurrentState() {
    if (fw_updated_) {
        properties_.find("updatestate")->second->SetValue(fwStates_.find(FW_UPDATED)->second.c_str());
        bool is_fw_notif_enabled = device_->IsFwNotifyEnabled();

        if (is_fw_notif_enabled) {
            if (device_->SendNotification(fwStates_.find(FW_UPDATED)->second.c_str())) {
              fw_settings.version_ = device_->GetFirmwareVersion().toInt();
               properties_.find("version")->second->SetValue(String(fw_settings.version_));
               fw_updated_ = false;
            }
        } else {
            fw_updated_ = false;
        }
        SaveFwSettings();
    }

    CheckFirmware(fw_settings.version_);

    if (properties_.find("staging")->second->HasNewValue()) {
        String str_staging_status = properties_.find("staging")->second->GetValue();
        fw_settings.staging_status = str_staging_status == "true" ? true : false;

        new_fw_settings_ = true;
        properties_.find("staging")->second->SetHasNewValue(false);

        if (!fw_settings.staging_status) {
            Serial.println("[D] staging_status == false");
            force_update_ = true;
            CheckFirmware(properties_.find("version")->second->GetValue().toInt());
        }
    }

    if (properties_.find("updatetime")->second->HasNewValue()) {
        SetUpdateTime(properties_.find("updatetime")->second->GetValue());
        properties_.find("updatetime")->second->SetHasNewValue(false);
        new_fw_settings_ = true;
    }

    if (properties_.find("autoupdate")->second->HasNewValue()) {
        fw_settings.autoUpdate_ = properties_.find("autoupdate")->second->GetValue() == "true";
        properties_.find("autoupdate")->second->SetHasNewValue(false);
        new_fw_settings_ = true;
    }

    if (properties_.find("update")->second->HasNewValue()) {
        properties_.find("update")->second->SetValue("");
        properties_.find("update")->second->SetHasNewValue(false);
        force_update_ = true;
    }

    if ((millis() - period_loop > kLoopDelay_)) {
        if (new_fw_settings_) {
            if (SaveFwSettings()) new_fw_settings_ = false;
        }
        period_loop = millis();
    }
}

void AutoUpdateFw::CheckUpdate() {
    String firmware_state = fwStates_.find(FW_CHECK)->second.c_str();
    properties_.find("updatestate")->second->SetValue(firmware_state);
    if (fw_settings.staging_status) {
        fw_settings.staging_update_notify = true;
        new_fw_settings_ = true;
        Serial.println("[D] Updating to new staging firmware...");
        UpdateFirmware();
    } else if (CheckFirmwareVersion() != properties_.find("version")->second->GetValue().toInt()) {
        Serial.println("Available new firmware");
        UpdateFirmware();
    } else {
        String firmware_state = fwStates_.find(FW_ACTUAL)->second.c_str();
        properties_.find("updatestate")->second->SetValue(firmware_state);
        Serial.println("Already on latest version");
        force_update_ = false;
    }
}

void AutoUpdateFw::CheckFirmware(uint8_t firmwareVer) {
    if (force_update_) CheckUpdate();

    if (millis() - last_millis_firmware_ > kFirmwareDelay_) {
        bool fw_auto_update = properties_.find("autoupdate")->second->GetValue() == "true";
        if (fw_auto_update && time_client_ && device_->IsConnected()) {
            Serial.print("[i] auto update is ON, ");
            uint8_t hours = time_client_->GetHours();
            uint8_t minutes = time_client_->GetMinutes();
            Serial.printf("actual time is %i:%i\n", hours, minutes);
            if (hours == fw_settings.hours_) {
                if (minutes == fw_settings.minutes_) CheckUpdate();
            }
        }
        last_millis_firmware_ = millis();
    }
}


uint8_t AutoUpdateFw::CheckFirmwareVersion() {
    uint8_t new_version = 0;
    HTTPClient httpClient;
    String url = "https://" + host + kUrlFirmwareVersionPath_ + product_id + "/firmware-version";
    Serial.println("[D]CheckFirmwareVersion " + url);
    if (httpClient.begin(url)) {  // HTTPS
        int http_code = httpClient.GET();
        if (http_code == 200) {
            String newFWVersion = httpClient.getString();
            StaticJsonDocument<200> doc;
            deserializeJson(doc, newFWVersion);
            new_version = doc["firmware_version"];
        } else {
            Serial.print("Firmware version check failed, got HTTP response code ");
            Serial.println(http_code);
        }
        httpClient.end();
    }
    return new_version;
}

void AutoUpdateFw::UpdateFirmware() {
    if (new_fw_settings_) {
        if (SaveFwSettings()) new_fw_settings_ = false;
    }
    String firmware_state = fwStates_.find(FW_UPDATING)->second.c_str();
    properties_.find("updatestate")->second->SetValue(firmware_state);
    Serial.println("updating");
    HTTPClient httpClient;
    String apiPrefix = fw_settings.staging_status ? kUrlStagingFirmwareFilePath_ : kUrlFirmwareFilePath_;
    String url = "https://" + host + apiPrefix + product_id + ".bin";
    Serial.println("[D] UpdateFirmware " + url);
    if (httpClient.begin(url)) {  // HTTPS
        uint8_t update_status = httpUpdate.update(httpClient);
        switch (update_status) {
            case HTTP_UPDATE_FAILED:
                Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s", httpUpdate.getLastError(),
                              httpUpdate.getLastErrorString().c_str());
                firmware_state = fwStates_.find(FW_FAILED)->second.c_str();
                properties_.find("updatestate")->second->SetValue(firmware_state);
                force_update_ = false;
                break;

            case HTTP_UPDATE_NO_UPDATES:
                Serial.println("HTTP_UPDATE_NO_UPDATES");
                break;
        }
    }
}

bool AutoUpdateFw::LoadFwSettings() {
    ReadSettings("/fwconf.txt", reinterpret_cast<byte*>(&fw_settings), sizeof(fw_settings));

    String str_staging_status = fw_settings.staging_status ? "true" : "false";
    properties_.find("staging")->second->SetValue(str_staging_status);
    properties_.find("staging")->second->SetHasNewValue(false);

    uint16_t fw_ver_actual = device_->GetFirmwareVersion().toInt();
    uint16_t fw_ver_memory = fw_settings.version_;

    if (fw_ver_memory == 0) {
        Serial.println("[D] No version, probably 1st start");
        properties_.find("version")->second->SetValue(String(fw_ver_actual));
        fw_settings.version_ = fw_ver_actual;
        fw_ver_memory = fw_ver_actual;
    } else {
        properties_.find("version")->second->SetValue(String(fw_settings.version_));
        properties_.find("version")->second->SetHasNewValue(false);
    }

    if (fw_ver_actual != fw_ver_memory) {
        Serial.println("[i] Firmware updated");
        fw_updated_ = true;
    } else {
        if (fw_settings.staging_update_notify) {
            fw_settings.staging_update_notify = false;
            fw_updated_ = true;
            Serial.println("[i] Staging firmware updated");
        } else {
            String firmware_state = fwStates_.find(FW_ACTUAL)->second.c_str();
            properties_.find("updatestate")->second->SetValue(firmware_state);
        }
    }

    String auto_update_value = fw_settings.autoUpdate_ ? "true" : "false";
    properties_.find("autoupdate")->second->SetValue(auto_update_value);
    properties_.find("autoupdate")->second->SetHasNewValue(false);

    properties_.find("updatetime")->second->SetValue(TimeToStr(fw_settings.hours_, fw_settings.minutes_).c_str());
    properties_.find("updatetime")->second->SetHasNewValue(false);

    properties_.find("update")->second->SetValue("");
    properties_.find("update")->second->SetHasNewValue(false);

    return true;
}

void AutoUpdateFw::SetTimeClient(TimeClient* time_client) { this->time_client_ = time_client; }

void AutoUpdateFw::SetUpdateTime(String time) {
    uint8_t separator_pos = time.indexOf(":");
    if (separator_pos == 1 || separator_pos == 2) {
        uint8_t hours = time.substring(0, separator_pos).toInt();
        uint8_t minutes = time.substring(separator_pos + 1).toInt();
        if (hours < 24 && minutes < 60) {
            fw_settings.hours_ = hours;
            fw_settings.minutes_ = minutes;
            new_fw_settings_ = true;
        }
    }
}

bool AutoUpdateFw::SaveFwSettings() {
    return WriteSettings("/fwconf.txt", reinterpret_cast<byte*>(&fw_settings), sizeof(fw_settings));
}
