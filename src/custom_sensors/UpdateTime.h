#pragma once
#include <Arduino.h>

#include "homie.h"

// E_C -> ERROR_CODE
#define E_C_WRONG_FORMAT "WRONG_FORMAT"

// E_M -> ERROR_MESSAGE
#define E_M_WRONG_FORMAT "Invalid format, use XX:XX"
#define E_M_NON_DIGIT "Non digit input"
#define E_M_INVALID_INTERVAL "Invalid time interval"

class UpdateTime : public Property {
 public:
    UpdateTime(const char* name, const char* id, Node* node, PROPERTY_TYPE type, bool settable, bool retained,
             const char* data_type, String format = "", String unit = "");

    ~UpdateTime() { Serial.printf("Property UpdateTime %s destroyed\r\n", name_.c_str()); }

    virtual bool Init(Homie* homie);

    bool Validate(String value);
 private:
};
