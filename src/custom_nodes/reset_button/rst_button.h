#pragma once

#include <Arduino.h>

#include <map>
#include <string>

#include "device/device.h"
#include "node/node.h"

class RstButton : public Node {
 public:
    RstButton(const char* name, const char* id, Device* device);
    bool Init(Homie* homie);
    void HandleCurrentState();
 private:
    const uint16_t rLoopDelay_ = 5 * 1000;      // sec
    uint32_t period_loop = millis();
};
