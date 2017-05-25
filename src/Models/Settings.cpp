#include "Settings.hpp"

using namespace Models;

Settings::Settings(bool isOn, std::string uniqueName, std::string deviceName) :
  isOn(isOn), uniqueName(uniqueName), deviceName(deviceName) {
}
