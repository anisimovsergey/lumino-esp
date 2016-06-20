#include "Network.hpp"

using namespace Models;

Network::Network(
  String ssid,
  int rssi,
  int encryptionType) :
  ssid(ssid),
  rssi(rssi),
  encryptionType(encryptionType) {
}
