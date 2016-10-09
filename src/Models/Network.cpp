#include "Network.hpp"

using namespace Models;

Network::Network(
  std::string ssid,
  int rssi,
  std::string encryption) :
  ssid(ssid),
  rssi(rssi),
  encryption(encryption) {
}
