#include "wifi_client.h"

void WifiClient::SetCredentials(String ssid_name, String ssid_password) {
    ssid_name_ = ssid_name;
    ssid_password_ = ssid_password;
    pinMode(kLedStatus_, OUTPUT);
    digitalWrite(kLedStatus_, LOW);
}

bool WifiClient::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

bool WifiClient::Connect() {
    if (WiFi.status() != WL_CONNECTED) {  // If not connected
        wifi_connected = false;

        if (millis() - wifi_reconnect_time_ > kWifiReconnectDelay_) {
            WiFi.mode(WIFI_STA);
            WiFi.begin(ssid_name_.c_str(), ssid_password_.c_str());
            WiFi.setAutoReconnect(true);
            WiFi.persistent(true);

            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
            Serial.println(ssid_name_);
            Serial.println(ssid_password_);

            wifi_reconnect_time_ = millis();
        } else if (millis() - kBlinkingPairingDelay_ > last_blink_time_) {
            last_blink_time_ = millis();
            Serial.print(".");
            digitalWrite(kLedStatus_, !digitalRead(kLedStatus_));
        }

        return false;
    }

    if (!wifi_connected) {
        wifi_connected = true;
        digitalWrite(kLedStatus_, LOW);
    }

    return true;
}
