#include "WiFiManager.hpp"
#include <ESP8266WiFi.h>

using namespace Core;
using namespace Models;
using namespace Services;

WiFiManager::WiFiManager() {
  network = "Network";
}

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

bool
WiFiManager::hasConnection() const {
  return (getNetwork().length() > 0);
}

String
WiFiManager::getDeviceName() const {
  return "Device name";
}

String
WiFiManager::getNetwork() const {
  return network;
}

String
WiFiManager::getPassword() const {
  return "Password";
}

bool
WiFiManager::isConnected() const {
  return (WiFi.status() == WL_CONNECTED);
}

Status
WiFiManager::connect(String network, String password) {
  if (network == "Network") {
    this->network = network;
    return Status::Ok;
  } else
    return Status::UnableToConnect;
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

Status
WiFiManager::disconnect() {
  network = "";
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
  return Status::Ok;
}
