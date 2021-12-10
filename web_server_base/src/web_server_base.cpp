#include "web_server_base.h"

#include <ArduinoJson.h>

#include "file_system/src/file_system.h"
#include "utils/src/utils.h"

WebServerBase::WebServerBase(Device *device) {
    this->device_ = device;
    // cppcheck-suppress noCopyConstructor
    // cppcheck-suppress noOperatorEq
    this->server_ = new AsyncWebServer(kPort_);
}

void WebServerBase::Init() { SetupWebServer(); }

void WebServerBase::SetupWebServer() {
    server_->on("/healthcheck", HTTP_GET,
                [](AsyncWebServerRequest *request) { request->send(200, "text/html", "OK"); });

    server_->on("/pair", HTTP_GET, [this](AsyncWebServerRequest *request) {
        if (!request->hasParam("ssid") || !request->hasParam("psk") || !request->hasParam("wsp") ||
            !request->hasParam("token") || !request->hasParam("host") || !request->hasParam("brport")) {
            request->send(400, "text/plain", "Incorrect data");
            return;
        }

        ssid_name = request->getParam("ssid")->value();
        ssid_password = request->getParam("psk")->value();
        person_mail = request->getParam("wsp")->value();
        token = request->getParam("token")->value();
        host = request->getParam("host")->value();
        broker_port = request->getParam("brport")->value();

        String devId = WiFi.macAddress();
        devId.toLowerCase();
        devId.replace(":", "-");
        device_id = devId;
        person_id = Sha256(person_mail);
        Serial.println("WebServer update:");
        Serial.println("SSID_Name = " + ssid_name);
        Serial.println("SSID_Password = " + ssid_password);
        Serial.println("person_mail = " + person_mail);
        Serial.println("person_id = " + person_id);
        Serial.println("token = " + token);
        Serial.println("host = " + host);
        Serial.println("brport = " + broker_port);
        Serial.println("device_id = " + device_id);
        if (ssid_name == "") {
            request->send(400, "text/plain", "Wifi name is NULL");
            return;
        }
        if (!SaveConfig()) {
            request->send(500, "text/plain", "Server error");
            return;
        }

        request->send(200, "text/plain", "OK");
        delay(kResponseDelay_);
        ESP.restart();
    });

    server_->onNotFound([](AsyncWebServerRequest *request) { request->send(404); });

    server_->begin();
}
