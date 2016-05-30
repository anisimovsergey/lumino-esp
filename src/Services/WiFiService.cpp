#include "WiFiService.hpp"

#include "Core/Status.hpp"
#include "Core/Logger.hpp"
#include "Models/Network.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Models;
using namespace Services;

Status
WiFiService::getWiFiNetworks(Networks& networks) const {
  Logger::message("Scanning networks...");
  int networksCount = WiFi.scanNetworks();
  Logger::message("Networks scanned");
  if (networksCount >= 0) {
    for (int networkNum = 0; networkNum < networksCount; networkNum++) {
      Logger::message("Getting ssid");
      String ssid = WiFi.SSID(networkNum);
      Logger::message("Getting rssi");
      int rssi = WiFi.RSSI(networkNum);
      Logger::message("Getting encryptionType");
      int encryptionType = WiFi.encryptionType(networkNum);
      Logger::message("Adding network");
      networks.add(Network(ssid, rssi, encryptionType));
    }
    return Status::Ok;
  } else {
    Logger::message("Networks scanning errpr");
    return Status::UnableToScanFiFiNetworks;
  }
}
