#include "WiFiManager.hpp"
#include "Core/Memory.hpp"
#include "Core/Format.hpp"
#include "Models/Connection.hpp"

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

using namespace Core;
using namespace Models;
using namespace Messaging;
using namespace Services;

using namespace std::placeholders;

WiFiManager::WiFiManager(
  Settings::Shared settings,
  IMessageQueue::Shared messageQueue) :
  settings(settings),
  messageQueue(messageQueue) {

  dnsServer = std::move(Core::makeUnique<DNSServer>());
  isConnectedInternal = false;

  connectionController = messageQueue->createController(Connection::TypeId());
  connectionController->addOnRequest("get", std::bind(&WiFiManager::onGetConnection, this));
  connectionController->addOnRequest<Connection>("create", std::bind(&WiFiManager::onCreateConnection, this, _1));
  connectionController->addOnRequest("delete", std::bind(&WiFiManager::onDeleteConnection, this));

  accessPointController = messageQueue->createController(AccessPoint::TypeId());
  accessPointController->addOnRequest("get", std::bind(&WiFiManager::onGetAccessPoint, this));

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

Core::Status
WiFiManager::connect(std::string network, std::string password) {

  if (isConnected())
    return Status(StatusCode::Conflict, "The connection already exists.");

  WiFi.begin(network.c_str(), password.c_str());
  return Status::OK;
}

Core::Status
WiFiManager::disconnect() {

  if (!hasConnection())
    return Status(StatusCode::Conflict, "The connection doesn't exist.");

  WiFi.disconnect();
  return Status::OK;
}

void
WiFiManager::startSoftAP() {
  // Set access point name (SSID)
  WiFi.softAP(settings->getUniqueName().c_str());
  dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer->start(53, "*", WiFi.softAPIP());
  accessPointController->sendEvent("created", createAccessPointObject());
}

void
WiFiManager::stopSoftAP() {
  dnsServer->stop();
  WiFi.softAPdisconnect();
  WiFi.enableAP(false);
  accessPointController->sendEvent("deleted");
}

void
WiFiManager::idle() {
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

Core::IEntity::Unique
WiFiManager::onGetConnection() {
  if (hasConnection()) {
    return createConnectionObject();
  } else {
    return Status::makeUnique(StatusCode::NotFound, "The connection doesn't exist.");
  }
}

Core::IEntity::Unique
WiFiManager::onCreateConnection(const Models::Connection& connection) {

  auto result = connect(connection.getNetworkSsid(), connection.getNetworkPassword());
  if (!result.isOk()) {
    return Status::makeUnique(StatusCode::InternalServerError,
      "Unable to create the connection.", std::move(result));
  }

  connectionController->sendEvent("created", createConnectionObject());
  return Status::makeUnique(StatusCode::Created, "The connection was created.");
}

Core::IEntity::Unique
WiFiManager::onDeleteConnection() {

  auto result = disconnect();
  if (!result.isOk()) {
    return Status::makeUnique(StatusCode::InternalServerError,
      "Unable to delete the connection.", std::move(result));
  }

  connectionController->sendEvent("deleted");
  return Status::makeUnique(StatusCode::NoContent, "The connection was deleted.");
}

Core::IEntity::Unique
WiFiManager::onGetAccessPoint() {
  if (hasAccessPoint()) {
    return createAccessPointObject();
  } else {
    return Status::makeUnique(StatusCode::NotFound, "The access point doesn't exist.");
  }
}

void
WiFiManager::onConnected() {
  if (hasConnection() && !isConnectedInternal) {
    if (MDNS.begin(settings->getUniqueName().c_str())) {
      MDNS.addService("http", "tcp", 80);
    }
    isConnectedInternal = true;
    connectionController->sendEvent("updated", createConnectionObject());
  }
}

void
WiFiManager::onDisconnected() {
  if (hasConnection() && isConnectedInternal) {
    isConnectedInternal = false;
    connectionController->sendEvent("updated", createConnectionObject());
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
