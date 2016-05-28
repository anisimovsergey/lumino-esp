#include "WiFiService.hpp"

#include "Models/Network.hpp"
#include "Core/Status.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Models;
using namespace Services;

Status
WiFiService::getWiFiNetworks(Networks& networks) const {
  int networksCount = WiFi.scanNetworks();
  if (networksCount == -1)
    return Status::UnableToScanFiFiNetworks;

  for (int networkNum = 0; networkNum < networksCount; networkNum++) {
    String ssid = WiFi.SSID(networkNum);
    int rssi = WiFi.RSSI(networkNum);
    int encryptionType = WiFi.encryptionType(networkNum);
    networks.add(Network(ssid, rssi, encryptionType));
  }
  return Status::Ok;
}
