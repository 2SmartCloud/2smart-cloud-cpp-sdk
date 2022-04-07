#pragma once
#include <Arduino.h>

#include <string>

std::string RandomString(uint8_t length);
std::string RandomString(uint32_t seed, uint8_t length);

String TimeToStr(uint8_t hours, uint8_t minutes);

String Sha256(String data);
