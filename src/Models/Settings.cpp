#include "Settings.hpp"

using namespace Models;

Settings::Settings(String deviceName, String networkSsid,
  String networkPassword, bool isConnected) :
  deviceName(deviceName), networkSsid(networkSsid),
  networkPassword(networkPassword), isConnected(isConnected) {
}
