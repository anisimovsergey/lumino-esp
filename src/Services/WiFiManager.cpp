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

WiFiManager::~WiFiManager() {
}

void
WiFiManager::initialize() {
  WiFi.mode(WIFI_STA);
  WiFi.hostname(deviceName.c_str());
  startSoftAP();
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
    return StatusResult::Conflict("The connection already exists.");

  WiFi.begin(network.c_str(), password.c_str());
  return StatusResult::OK();
}

void
WiFiManager::loop() {
  dnsServer->processNextRequest();
}

std::unique_ptr<Core::StatusResult>
WiFiManager::disconnect() {

  if (!hasConnection())
    return StatusResult::Conflict("The connection doesn't exist.");

  WiFi.disconnect();
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

/*
std::unique_ptr<IActionResult>
WiFiManager::onCreateConnection(const CreateConnectionMessage& message) {

  auto result = connect(message->getConnection());

  if (!result->isOk())
    return StatusResult::InternalServerError("Unable to create the connection.",
      std::move(result));

  return RedirectResult::ToRoute(message->getConnectionUrl());
}

std::unique_ptr<IActionResult>
WiFiManager::onGetConnection() {

  if (!hasConnection())
    return StatusResult::NotFound("The connection doesn't exist.");

  return ObjectResult::OK(
    make_unique<Connection>(
      getNetwork(),
      isConnected()
    ));
}

std::unique_ptr<IActionResult>
WiFiManager::onDeleteConnection() {

  auto result = disconnect();
  if (!result->isOk())
    return StatusResult::InternalServerError("Unable to delete the connection.",
      std::move(result));

  return StatusResult::OK();
}

std::unique_ptr<IActionResult>
WiFiManager::onGetWiFiNetworks() const {

  auto scanStatus = WiFi.scanComplete();
  if (scanStatus != WIFI_SCAN_RUNNING && scanStatus < 0) {
    // Scan networks asynchronously
    WiFi.scanNetworks(true);
    auto message = StatusResult::OK("WiFi networks scanning is started.");
    messageQueue->addMessage(message);
  }
}

void
WiFiManager::onScanComplete() {

  Message message;
  auto networksCount = WiFi.scanComplete();
  if (networksCount >= 0) {
    auto networks = make_unique<List<Network>>();
    for (int networkNum = 0; networkNum < networksCount; networkNum++) {
      String ssid = WiFi.SSID(networkNum);
      int rssi = WiFi.RSSI(networkNum);
      int encryptionType = WiFi.encryptionType(networkNum);
      networks->add(Network(ssid, rssi, encryptionType));
    }
    WiFi.scanDelete();
    message = ObjectResult::OK(std::move(networks));
  } else {
    message = StatusResult::InternalServerError("Unable to scan WiFi networks.");
  }
  messageQueue->addMessage(message);
}
*/
