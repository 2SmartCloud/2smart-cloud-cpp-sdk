#include "WifiSignal.h"

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
    int8_t dBm = (WiFi.RSSI());
    uint8_t wifiQuality = 2 * (dBm + 100);
    if (wifiQuality > 100) wifiQuality = 100;
    if (wifi_client.isConnected()) {
    this->SetValue(String(wifiQuality));
    }
    // Serial.println("[D] RSSI: " + String(dBm));
    Serial.println("[D] WIFI %: " + String(wifiQuality));
  }
}

void WifiSignal::HandleSettingNewValue() {}
