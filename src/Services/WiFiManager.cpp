#include "WiFiManager.hpp"
#include "Core/Logger.hpp"
#include "Core/Memory.hpp"
#include "Core/StringFormat.hpp"
#include "Core/ObjectResult.hpp"
#include "Models/Connection.hpp"

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

using namespace Core;
using namespace Models;
using namespace Services;
using namespace std::placeholders;

WiFiManager::WiFiManager(
  Services::Settings::Shared settings,
  Core::IMessageQueue::Shared messageQueue) :
  settings(settings),
  messageQueue(messageQueue) {

  dnsServer = std::move(Core::makeUnique<DNSServer>());
  isConnectedInternal = false;

  auto queueController = messageQueue->createController("WiFiManager");

  connectionController = QueueResourceController<Connection>::makeUnique(queueController);
  connectionController->setOnGetRequestHandler(std::bind(&WiFiManager::onGetConnection, this));
  connectionController->setOnCreateRequestHandler(std::bind(&WiFiManager::onCreateConnection, this, _1));
  connectionController->setOnDeleteRequestHandler(std::bind(&WiFiManager::onDeleteConnection, this));

  accessPointController = QueueResourceController<AccessPoint>::makeUnique(queueController);
  accessPointController->setOnGetRequestHandler(std::bind(&WiFiManager::onGetAccessPoint, this));

  connectedEventHandler = WiFi.onStationModeGotIP(
    [=](const WiFiEventStationModeGotIP&) { onConnected(); }
  );

  disconnectedEventHandler = WiFi.onStationModeDisconnected(
    [=](const WiFiEventStationModeDisconnected& e) { onDisconnected(); }
  );

  clientConnectedEventHandler = WiFi.onSoftAPModeStationConnected(
    [=](const WiFiEventSoftAPModeStationConnected&) { onClientConnected(); }
  );

  clientDisconnectedEventHandler = WiFi.onSoftAPModeStationDisconnected(
    [=](const WiFiEventSoftAPModeStationDisconnected&) {  onClientDisconnected(); }
  );
}

WiFiManager::~WiFiManager() {
}

void
WiFiManager::start() {
  // Set DHCP host name
  WiFi.hostname(settings->getUniqueName().c_str());
  startSoftAP();
  startDisconnectTimer();
}

bool
WiFiManager::hasConnection() const {
  return (WiFi.SSID().length() > 0);
}

bool
WiFiManager::hasAccessPoint() const {
  auto currentMode = WiFi.getMode();
  return ((currentMode & WIFI_AP) != 0);
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
WiFiManager::startSoftAP() {
  // Set access point name (SSID)
  WiFi.softAP(settings->getUniqueName().c_str());
  dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer->start(53, "*", WiFi.softAPIP());
  accessPointController->sendCreateNotification(createAccessPointObject());
}

void
WiFiManager::stopSoftAP() {
  dnsServer->stop();
  WiFi.softAPdisconnect();
  WiFi.enableAP(false);
  accessPointController->sendDeleteNotification();
}

void
WiFiManager::loop() {
  dnsServer->processNextRequest();
}

Models::Connection::Unique
WiFiManager::createConnectionObject() {
  return Connection::makeUnique(getNetwork(), isConnected());
}

Models::AccessPoint::Unique
WiFiManager::createAccessPointObject() {
  return AccessPoint::makeUnique(settings->getUniqueName());
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

  connectionController->sendCreateNotification(createConnectionObject());
  return StatusResult::makeUnique(StatusCode::Created, "The connection was created.");
}

StatusResult::Unique
WiFiManager::onDeleteConnection() {

  auto result = disconnect();
  if (!result->isOk()) {
    return StatusResult::makeUnique(StatusCode::InternalServerError,
      "Unable to delete the connection.", std::move(result));
  }

  connectionController->sendDeleteNotification();
  return StatusResult::makeUnique(StatusCode::NoContent, "The connection was deleted.");
}

ActionResult::Unique
WiFiManager::onGetAccessPoint() {
  if (hasAccessPoint()) {
    return ObjectResult::makeUnique(StatusCode::OK, createAccessPointObject());
  } else {
    return StatusResult::makeUnique(StatusCode::NotFound, "The access point doesn't exist.");
  }
}

void
WiFiManager::onConnected() {
  if (hasConnection() && !isConnectedInternal) {
    if (MDNS.begin(settings->getUniqueName().c_str())) {
      MDNS.addService("http", "tcp", 80);
    }
    isConnectedInternal = true;
    connectionController->sendUpdateNotification(createConnectionObject());
  }
}

void
WiFiManager::onDisconnected() {
  if (hasConnection() && isConnectedInternal) {
    isConnectedInternal = false;
    connectionController->sendUpdateNotification(createConnectionObject());
  }
}

void
WiFiManager::onClientConnected() {
  stopDisconnectTimer();
}

void
WiFiManager::onClientDisconnected() {
  if (WiFi.softAPgetStationNum() == 0) {
    startDisconnectTimer();
  }
}

void
WiFiManager::onDisconnectStatic(WiFiManager* manager) {
  manager->onDisconnectTimeout();
}

void
WiFiManager::startDisconnectTimer() {
  disconnectTimer.once(300, onDisconnectStatic,  this);
}

void
WiFiManager::stopDisconnectTimer() {
  disconnectTimer.detach();
}

void
WiFiManager::onDisconnectTimeout() {
  stopSoftAP();
}
