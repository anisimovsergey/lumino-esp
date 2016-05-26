#include "Network.hpp"

Network::Network(String ssid, int rssi, int encryptionType) {
  this->ssid = ssid;
  this->rssi = rssi;
  this->encryptionType = encryptionType;
}
