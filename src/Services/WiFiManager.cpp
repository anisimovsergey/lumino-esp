#include "WiFiManager.hpp"
#include "Core/Logger.hpp"
#include "Core/Utils.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Models;
using namespace Services;

#define MAX_CONNECTION_WAIT 10

WiFiManager::WiFiManager() {
  network = "BTHub4-NC8S";
  password = "d5e89ca8cf";
  deviceName = "esp8266fs";
  dnsServer = std::unique_ptr<DNSServer>(new DNSServer());
}

void
WiFiManager::initialize() {
  WiFi.mode(WIFI_STA);
  WiFi.hostname(deviceName.c_str());
  disconnect();
}

Core::Status
WiFiManager::getWiFiNetworks(Networks& networks) const {
  auto networksCount = WiFi.scanComplete();
  if (networksCount == WIFI_SCAN_RUNNING) {
    Logger::message("Scanning networks... ");
    return Status::Ok;
  }
  if (networksCount >= 0) {
    Logger::message("Networks scanned " + String(networksCount));
    for (int networkNum = 0; networkNum < networksCount; networkNum++) {
      String ssid = WiFi.SSID(networkNum);
      int rssi = WiFi.RSSI(networkNum);
      int encryptionType = WiFi.encryptionType(networkNum);
      networks.add(Network(ssid, rssi, encryptionType));
    }
    WiFi.scanDelete();
    return Status::Ok;
  }
  WiFi.scanNetworks(true);
  Logger::message("Scan started");
  return Status::Ok;
}

bool
WiFiManager::hasConnection() const {
  return (getNetwork().length() > 0);
}

String
WiFiManager::getDeviceName() const {
  return deviceName;
}

String
WiFiManager::getNetwork() const {
  return network;
}

bool
WiFiManager::isConnected() const {
  return (WiFi.status() == WL_CONNECTED);
}

Status
WiFiManager::connect(String network, String password) {

  WiFi.begin(network.c_str(), password.c_str());
  int i = 0;
  while ((WiFi.status() != WL_CONNECTED) && i < MAX_CONNECTION_WAIT) {
    delay(1000);
    i++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    this->network = network;
    this->password = password;
    WiFi.softAPdisconnect();
    return Status::Ok;
  }

  return Status::UnableToConnect;
}

void
WiFiManager::loop() {
  dnsServer->processNextRequest();
}

Status
WiFiManager::disconnect() {
  if (WiFi.status() != WL_DISCONNECTED)
    WiFi.disconnect();
  network = "";
  password = "";

  Logger::message("Configuring access point """ + deviceName + """ ");
  WiFi.softAP(deviceName.c_str());
  delay(500);
  Logger::message("Access point IP address: " + Utils::toStringIp(WiFi.softAPIP()));

  Logger::message("Configuring captive DNS");
  dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer->start(53, "*", WiFi.softAPIP());

  return Status::Ok;
}
