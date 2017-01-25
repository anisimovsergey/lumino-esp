#include "Settings.hpp"
#include "Core/Format.hpp"

#include <ESP8266WiFi.h>
#include <EEPROM.h>

using namespace Core;
using namespace Models;
using namespace Services;

namespace {
  static const int EEPROM_COLOR_START = 0;
  static const int EEPROM_COLOR_END   = 2;
  static const int EEPROM_NAME_START  = 5;
  static const int EEPROM_NAME_END    = 36;
}

std::string
Settings::getUniqueName() const {
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

std::string
Settings::getDeviceName() const {
  std::string name;
  for (size_t i = EEPROM_NAME_START; i <= EEPROM_NAME_END; i++) {
    auto ch = EEPROM.read(i);
    if (ch != 0)
      name += ch;
  }
  return name;
}

void
Settings::setDeviceName(std::string name) {
  for (size_t i = EEPROM_NAME_START; i <= EEPROM_NAME_END; i++) {
    char ch = 0;
    size_t index = i - EEPROM_NAME_START;
    if (index < name.length())
      ch = name[index];
    EEPROM.write(i, ch);
  }
}

Models::Color
Settings::getColor() const {
  int address = EEPROM_COLOR_START;
  auto r = EEPROM.read(address++);
  auto g = EEPROM.read(address++);
  auto b = EEPROM.read(address++);
  return Color(r, g, b);
}

void
Settings::setColor(const Models::Color& color) {
  int address = EEPROM_COLOR_START;
  EEPROM.write(address++, color.getR());
  EEPROM.write(address++, color.getG());
  EEPROM.write(address++, color.getB());
}
