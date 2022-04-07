#pragma once

#include <Arduino.h>

#include "homie.h"

#define WIFI_SIGNAL "signal"

extern WifiClient wifi_client;

class WifiSignal : public Property {
 public:
    WifiSignal(const char* name, const char* id, Device* device, PROPERTY_TYPE type, bool settable, bool retained,
          const char* data_type);
    WifiSignal(const char* name, const char* id, Node* node, PROPERTY_TYPE type, bool settable, bool retained,
          const char* data_type);
    WifiSignal(const char* name, int id, Node* node, PROPERTY_TYPE type, bool settable, bool retained,
          const char* data_type);

    bool Init(Homie* homie);

    void HandleCurrentState();

    void HandleSettingNewValue();

 private:
    const uint16_t wPeriodDelay_ = 5 * 1000;  // update wifi signal interval
    uint32_t rssi_period_timer_ = millis();
};
