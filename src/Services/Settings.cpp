#include "Settings.hpp"
#include "Core/StringFormat.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Services;

std::string
Settings::getDeviceName() const {
  return "esp8266fs";
}

std::string
Settings::getLocalDomain() const {
  return ipToString(WiFi.softAPIP());
}

int
Settings::getWebServerPort() const {
  return 80;
}
