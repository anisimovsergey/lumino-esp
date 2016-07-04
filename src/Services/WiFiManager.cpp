#include "WiFiManager.hpp"
#include "Core/Logger.hpp"
#include "Core/Utils.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Models;
using namespace Services;

WiFiManager::WiFiManager(std::shared_ptr<Core::IMessageQueue> messageQueue) :
  dnsServer(make_unique<DNSServer>()), messageQueue(messageQueue) {
  deviceName = "esp8266fs";
}

void
WiFiManager::initialize() {
  WiFi.mode(WIFI_STA);
  WiFi.hostname(deviceName.c_str());
  // Start soft AP without checking connection.
  startSoftAP();
}

std::unique_ptr<Core::StatusResult>
WiFiManager::getWiFiNetworks(
  std::unique_ptr<List<Network>>& networks) const {
  networks = make_unique<List<Network>>();
  auto networksCount = WiFi.scanComplete();
  if (networksCount == WIFI_SCAN_RUNNING) {
  } else if (networksCount >= 0) {
    for (int networkNum = 0; networkNum < networksCount; networkNum++) {
      String ssid = WiFi.SSID(networkNum);
      int rssi = WiFi.RSSI(networkNum);
      int encryptionType = WiFi.encryptionType(networkNum);
      networks->add(Network(ssid, rssi, encryptionType));
    }
    WiFi.scanDelete();
  } else {
    WiFi.scanNetworks(true);
  }
  return StatusResult::OK();
}

bool
WiFiManager::hasConnection() const {
  return (WiFi.SSID().length() > 0);
}

String
WiFiManager::getDeviceName() const {
  return deviceName;
}

String
WiFiManager::getNetwork() const {
  return WiFi.SSID();
}

bool
WiFiManager::isConnected() const {
  return (WiFi.status() == WL_CONNECTED);
}

std::unique_ptr<Core::StatusResult>
WiFiManager::connect(String network, String password) {
  if (isConnected())
    return StatusResult::Conflict("Already connected.");

  messageQueue->post([&](){
    WiFi.begin(network.c_str(), password.c_str());
  });
  return StatusResult::OK();
}

void
WiFiManager::loop() {
  dnsServer->processNextRequest();
}

std::unique_ptr<Core::StatusResult>
WiFiManager::disconnect() {
  if (!hasConnection())
    return StatusResult::Conflict("Connection doesn't exist.");

  messageQueue->post([&](){
    WiFi.disconnect();
  });
  return StatusResult::OK();
}

void
WiFiManager::startSoftAP() {
  WiFi.softAP(deviceName.c_str());
  delay(500);
  dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer->start(53, "*", WiFi.softAPIP());
}

void
WiFiManager::stopSoftAP() {
  WiFi.softAPdisconnect();
}
