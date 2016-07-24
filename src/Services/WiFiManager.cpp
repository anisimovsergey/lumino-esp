#include "WiFiManager.hpp"
#include "Core/Logger.hpp"
#include "Core/Utils.hpp"
#include "Models/Connection.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Models;
using namespace Services;
using namespace std::placeholders;

namespace {
  static const String SenderId = "WiFiManager";
  static const String ConnectionResource = "/connection";
}

WiFiManager::WiFiManager(std::shared_ptr<Core::IMessageQueue> messageQueue) :
  dnsServer(make_unique<DNSServer>()), messageQueue(messageQueue) {
  deviceName = "esp8266fs";

  auto queueController = messageQueue->createController(SenderId);
  controller = QueueResourceController<Connection>::makeUnique(queueController);

  controller->setOnGetRequestHandler(
    std::bind(&WiFiManager::onGetConnection, this));
  controller->setOnCreateRequestHandler(
    std::bind(&WiFiManager::onCreateConnection, this, _1));
  controller->setOnDeleteRequestHandler(
    std::bind(&WiFiManager::onDeleteConnection, this));

  connectedEventHandler = WiFi.onStationModeGotIP(
    [=](const WiFiEventStationModeGotIP&) {
      onConnected();
    }
  );

  disconnectedEventHandler = WiFi.onStationModeDisconnected(
    [=](const WiFiEventStationModeDisconnected&) {
      onDisconnected();
    }
  );
}

WiFiManager::~WiFiManager() {
}

void
WiFiManager::start() {
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
  return WiFi.isConnected();
}

std::unique_ptr<Core::StatusResult>
WiFiManager::connect(String network, String password) {

  if (isConnected())
    return StatusResult::Conflict("The connection already exists.");

  WiFi.begin(network.c_str(), password.c_str());
  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
WiFiManager::disconnect() {

  if (!hasConnection())
    return StatusResult::Conflict("The connection doesn't exist.");

  WiFi.disconnect();
  return StatusResult::OK();
}

void
WiFiManager::loop() {
  dnsServer->processNextRequest();
}

Models::Connection::Unique
WiFiManager::createConnectionObject() {
  return Connection::makeUnique(getNetwork(), isConnected());
}

IActionResult::Unique
WiFiManager::onGetConnection() {
  if (hasConnection()) {
    return ObjectResult::OK(createConnectionObject());
  } else {
    return StatusResult::NotFound("The connection doesn't exist.");
  }
}

StatusResult::Unique
WiFiManager::onCreateConnection(const Models::Connection& connection) {

  auto result = connect(connection.getNetworkSsid(), connection.getNetworkPassword());
  if (!result->isOk()) {
    return StatusResult::InternalServerError("Unable to create the connection.",
      std::move(result));
  }

  controller->sendCreateNotification(createConnectionObject());
  return StatusResult::Created("the connection was created.");
}

StatusResult::Unique
WiFiManager::onDeleteConnection() {

  auto result = disconnect();
  if (!result->isOk()) {
    return StatusResult::InternalServerError("Unable to delete the connection.",
      std::move(result));
  }

  controller->sendDeleteNotification();
  return StatusResult::NoContent("The connection was deleted.");
}

void
WiFiManager::onConnected() {
  if (hasConnection()) {
    controller->sendUpdateNotification(createConnectionObject());
  }
}

void
WiFiManager::onDisconnected() {
  if (hasConnection()) {
    controller->sendUpdateNotification(createConnectionObject());
  }
}

void
WiFiManager::startSoftAP() {
  auto ipAddress = WiFi.softAP(deviceName.c_str());
  dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer->start(53, "*", ipAddress);
}

void
WiFiManager::stopSoftAP() {
  WiFi.softAPdisconnect();
}
