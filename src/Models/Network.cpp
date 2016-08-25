#include "Network.hpp"

using namespace Models;

Network::Network(
  std::string ssid,
  int rssi,
  int encryptionType) :
  ssid(ssid),
  rssi(rssi),
  encryptionType(encryptionType) {
}
