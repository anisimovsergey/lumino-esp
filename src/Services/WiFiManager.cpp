#include "WiFiManager.hpp"
#include "Core/Logger.hpp"
#include "Core/Memory.hpp"
#include "Core/ObjectResult.hpp"
#include "Models/Connection.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Models;
using namespace Services;
using namespace std::placeholders;

WiFiManager::WiFiManager(Core::IMessageQueue::Shared messageQueue) :
  dnsServer(Core::makeUnique<DNSServer>()), messageQueue(messageQueue) {
  deviceName = "esp8266fs";

  auto queueController = messageQueue->createController("WiFiManager");
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

std::string
WiFiManager::getDeviceName() const {
  return deviceName;
}

std::string
WiFiManager::getNetwork() const {
  return WiFi.SSID().c_str();
}

bool
WiFiManager::isConnected() const {
  return WiFi.isConnected();
}

Core::StatusResult::Unique
WiFiManager::connect(std::string network, std::string password) {

  if (isConnected())
    return StatusResult::makeUnique(StatusCode::Conflict, "The connection already exists.");

  WiFi.begin(network.c_str(), password.c_str());
  return StatusResult::OK();
}

Core::StatusResult::Unique
WiFiManager::disconnect() {

  if (!hasConnection())
    return StatusResult::makeUnique(StatusCode::Conflict, "The connection doesn't exist.");

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

ActionResult::Unique
WiFiManager::onGetConnection() {
  if (hasConnection()) {
    return ObjectResult::makeUnique(StatusCode::OK, createConnectionObject());
  } else {
    return StatusResult::makeUnique(StatusCode::NotFound, "The connection doesn't exist.");
  }
}

StatusResult::Unique
WiFiManager::onCreateConnection(const Models::Connection& connection) {

  auto result = connect(connection.getNetworkSsid(), connection.getNetworkPassword());
  if (!result->isOk()) {
    return StatusResult::makeUnique(StatusCode::InternalServerError,
      "Unable to create the connection.", std::move(result));
  }

  controller->sendCreateNotification(createConnectionObject());
  return StatusResult::makeUnique(StatusCode::Created, "The connection was created.");
}

StatusResult::Unique
WiFiManager::onDeleteConnection() {

  auto result = disconnect();
  if (!result->isOk()) {
    return StatusResult::makeUnique(StatusCode::InternalServerError,
      "Unable to delete the connection.", std::move(result));
  }

  controller->sendDeleteNotification();
  return StatusResult::makeUnique(StatusCode::NoContent, "The connection was created.");
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
