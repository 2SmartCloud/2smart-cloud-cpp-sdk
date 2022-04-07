#include "rst_button.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include "file_system/src/file_system.h"
#include "utils/src/utils.h"

volatile uint8_t resetProgress = 0;

RstButton::RstButton(const char * name,
  const char * id, Device * device): Node(name, id, device) {}

bool RstButton::Init(Homie * homie) {
  Node::Init(homie);
  return true;
}

void RstButton::HandleCurrentState() {
    if (properties_.find("resetbutton")->second->HasNewValue()) {
        resetProgress += 25;
        Serial.println("[D] RstButton CurrentState: " + String(resetProgress) + "%");

        properties_.find("resetstate")->second->SetValue(String(resetProgress));
        properties_.find("resetbutton")->second->SetValue("false");
        properties_.find("resetbutton")->second->SetHasNewValue(false);

        if (resetProgress == 100) {
          delay(500);
          EraseFlash();
        }
        period_loop = millis();
    }

    if (millis() - period_loop > rLoopDelay_) {
        if (resetProgress == 0) return;
        Serial.println("[D] CurrentState set to 0%");

        resetProgress = 0;
        properties_.find("resetstate")->second->SetValue(String(resetProgress));
    }
}
