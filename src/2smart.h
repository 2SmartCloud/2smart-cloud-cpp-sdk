#pragma once
#include <Arduino.h>
#include <custom_sensors/wifisignal/WifiSignal.h>
#include "homie.h"

class Cloud2Smart {
 public:
    Cloud2Smart();

    void setup();

    Device* GetDevice();

    void loop();

    ~Cloud2Smart() { Serial.println("2smart destroyed"); }

 private:
};

// ----------------------------------------------------------HTTP-----------
extern String ssid_name;      // WiFi name
extern String ssid_password;  // WiFi password
extern String person_mail;
extern String person_id;
extern String token;
extern String host;
extern String broker_port;
extern String web_auth_password;
extern const char* http_username;
// -------------------------------------------------------Production settings
extern String device_id;   // DeviceID/ MAC:adress
extern String product_id;  // production id
                           // -------------------------------------------------------MQTT variables

extern const char* device_name;
extern const char* device_version;
extern const char* firmware_name;

void HandleMessage(char* topic, byte* payload, unsigned int length);
