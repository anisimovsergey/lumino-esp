#include "WiFiService.hpp"
#include <ESP8266WiFi.h>
#include "../Models/Network.hpp"
#include "../Core/Status.hpp"

Status
WiFiService::getWiFiNetworks(std::list<Network>& networks) const {
  auto networksCount = WiFi.scanNetworks();
  if (networksCount == -1)
    return Status::UnableToScanFiFiNetworks;

  for (int networkNum = 0; networkNum < networksCount; networkNum++) {
    auto ssid = WiFi.SSID(networkNum);
    auto rssi = WiFi.RSSI(networkNum);
    auto encryptionType = WiFi.encryptionType(networkNum);
    Network network(ssid, rssi, encryptionType);
    networks.push_back(network);
  }
  return Status::Ok;
}
