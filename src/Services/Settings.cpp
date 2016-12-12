#include "Settings.hpp"

using namespace Services;

std::string
Settings::getDeviceName() const {
  return "esp8266fs";
}

int
Settings::getWebServerPort() const {
  return 80;
}
