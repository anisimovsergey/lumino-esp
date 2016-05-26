#include "WiFiService.hpp"
#include <ESP8266WiFi.h>
#include "Models/Network.hpp"
#include "Core/Status.hpp"

Status
WiFiService::getWiFiNetworks(std::list<Network>& networks) const {
  int networksCount = WiFi.scanNetworks();
  if (networksCount == -1)
    return Status::UnableToScanFiFiNetworks;

  for (int networkNum = 0; networkNum < networksCount; networkNum++) {
    String ssid = WiFi.SSID(networkNum);
    int rssi = WiFi.RSSI(networkNum);
    int encryptionType = WiFi.encryptionType(networkNum);
    networks.push_back(Network(ssid, rssi, encryptionType));
  }
  return Status::Ok;
}
