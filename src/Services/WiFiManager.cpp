#include "WiFiManager.hpp"
#include <ESP8266WiFi.h>

using namespace Core;
using namespace Models;
using namespace Services;

Core::Status
WiFiManager::getWiFiNetworks(Networks& networks) const {
  int networksCount = WiFi.scanNetworks();
  if (networksCount >= 0) {
    for (int networkNum = 0; networkNum < networksCount; networkNum++) {
      String ssid = WiFi.SSID(networkNum);
      int rssi = WiFi.RSSI(networkNum);
      int encryptionType = WiFi.encryptionType(networkNum);
      networks.add(Network(ssid, rssi, encryptionType));
    }
    return Status::Ok;
  } else {
    return Status::UnableToScanFiFiNetworks;
  }
}

String
WiFiManager::getDeviceName() const {

}

String
WiFiManager::getNetwork() const {

}

String
WiFiManager::getPassword() const {

}

bool
WiFiManager::isConnected() const {
  return (WiFi.status() == WL_CONNECTED);
}

void
WiFiManager::connect(String network, String password) {
  /*
  if (String(WiFi.SSID()) != network_ssid) {
    disconnectFromFiFi();
    WiFi.begin(network_ssid.c_str(), network_pswd.c_str());
    int i = 0;
    while ((WiFi.status() != WL_CONNECTED) && i < MAX_CONNECTION_WAIT) {
      delay(1000);
      i++;
    }
  }
  */
}

void
WiFiManager::disconnect() {
  /*
  if (WiFi.status() != WL_DISCONNECTED) {
    WiFi.disconnect();
    int i = 0;
    while ((WiFi.status() == WL_DISCONNECTED) && i < MAX_CONNECTION_WAIT) {
      delay(1000);
      i++;
    }
  }
  */
}
