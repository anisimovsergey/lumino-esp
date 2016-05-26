#include "Settings.hpp"

using namespace Models;

Settings::Settings(String deviceName,
                   String networkSsid,
                   String networkPassword) {
  this->deviceName = deviceName;
  this->networkSsid = networkSsid;
  this->networkPassword = networkPassword;
}
