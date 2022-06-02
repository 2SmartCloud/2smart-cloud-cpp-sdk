#include "WifiSignal.h"
#include "utils/src/utils.h"

WifiSignal::WifiSignal(const char * name,
  const char * id, Device * device, PROPERTY_TYPE type, bool settable, bool retained,
    const char * data_type): Property(name, id, device, type, settable, retained, data_type) {}
bool WifiSignal::Init(Homie * homie) {
  bool status = true;
  if (!Property::Init(homie)) status = false;
  return status;
}

void WifiSignal::HandleCurrentState() {
  if (millis() - rssi_period_timer_ > wPeriodDelay_) {
    rssi_period_timer_ = millis();
    int8_t dBm = WiFi.RSSI();
    uint8_t wifi_strenght = RSSIToPercent(dBm);
    if (wifi_client.isConnected()) {
    this->SetValue(String(wifi_strenght));
    }
    Serial.println("[i] WIFI %: " + String(wifi_strenght));
  }
}

void WifiSignal::HandleSettingNewValue() {}
