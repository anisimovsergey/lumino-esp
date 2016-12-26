#include "Settings.hpp"
#include "Core/StringFormat.hpp"

#include <ESP8266WiFi.h>
#include <EEPROM.h>

using namespace Core;
using namespace Models;
using namespace Services;

Settings::Settings() {
    readSettings();
}

std::string
Settings::getDeviceName() const {
  return "esp8266fs";
}

/** IP to String? */
String toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}


std::string
Settings::getLocalDomain() const {
  return toStringIp(WiFi.softAPIP()).c_str();
}

int
Settings::getWebServerPort() const {
  return 80;
}

Models::Color
Settings::getColor() const {
  return color;
}

void
Settings::setColor(const Models::Color& color) {
  this->color = color;
  writeSettings();
}

void
Settings::readSettings() {
  int address = 0;
  auto r = EEPROM.read(address++);
  auto g = EEPROM.read(address++);
  auto b = EEPROM.read(address++);
  color = Color(r, g, b);
}

void
Settings::writeSettings() {
  int address = 0;
  EEPROM.write(address++, color.getR());
  EEPROM.write(address++, color.getG());
  EEPROM.write(address++, color.getB());
}
