#include "custom_sensors/UpdateTime.h"

#include "file_system/src/file_system.h"

UpdateTime::UpdateTime(const char* name, const char* id, Node* node, PROPERTY_TYPE type, bool settable, bool retained,
                   const char* data_type, String format, String unit): Property(name, id, node,
                   type, settable, retained, data_type) {}

bool UpdateTime::Init(Homie * homie) {
  bool status = true;
  if ( !Property::Init(homie) ) status = false;
  return status;
}

bool UpdateTime::Validate(String value) {
    Serial.println("[D] Validate: " + value);

    int8_t separator_pos = value.indexOf(':');

    if ( separator_pos != 2 || value.length() > 5 ) {
        SetError(E_C_WRONG_FORMAT, E_M_WRONG_FORMAT);
        return false;
    }

    if ( !isdigit(value.charAt(0)) || !isdigit(value.charAt(separator_pos - 1)) ||
    !isdigit(value.charAt(separator_pos + 1)) || !isdigit(value.charAt(separator_pos + 2)) ) {
    SetError(E_C_WRONG_FORMAT, E_M_NON_DIGIT);
    return false;
    } else {
        uint8_t hours = value.substring(0, separator_pos).toInt();
        uint8_t minutes = value.substring(separator_pos + 1).toInt();
        Serial.println("[D]   hours: " + String(hours));
        Serial.println("[D] minutes: " + String(minutes));
        if ( hours < 24 && minutes < 60 ) {
            return true;
        } else {
        SetError(E_C_WRONG_FORMAT, E_M_INVALID_INTERVAL);
        return false;
        }
    }
}
