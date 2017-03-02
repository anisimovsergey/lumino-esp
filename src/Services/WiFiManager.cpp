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

WiFiManager::WiFiManager(
  IMessageQueue& messageQueue) :
  messageQueue(messageQueue) {

  dnsServer = std::move(std::make_unique<DNSServer>());
  isConnectedInternal = false;

  connectionController = messageQueue.createController(Connection::TypeId());
  connectionController->addOnRequest(RequestType::Read, [=](){
    return onGetConnection();
  });
  connectionController->addOnRequest(RequestType::Create, [=](const Models::Connection& connection){
    return onCreateConnection(connection);
  });
  connectionController->addOnRequest(RequestType::Delete, [=](){
    return onDeleteConnection();
  });

  accessPointController = messageQueue.createController(AccessPoint::TypeId());
  accessPointController->addOnRequest(RequestType::Read, [=](){
    return onGetAccessPoint();
  });

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
  WiFi.hostname(getUniqueName().c_str());
  startSoftAP();
  startDisconnectTimer();
}

std::string
WiFiManager::getUniqueName() const {
  return "esp8266fs";
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
  WiFi.softAP(getUniqueName().c_str());
  dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer->start(53, "*", WiFi.softAPIP());
  accessPointController->sendEvent(EventType::Created, createAccessPointObject());
}

void
WiFiManager::stopSoftAP() {
  dnsServer->stop();
  WiFi.softAPdisconnect();
  WiFi.enableAP(false);
  accessPointController->sendEvent(EventType::Deleted);
}

void
WiFiManager::idle() {
  dnsServer->processNextRequest();
}

std::unique_ptr<Connection>
WiFiManager::createConnectionObject() {
  return std::make_unique<Connection>(getNetwork(), isConnected());
}

std::unique_ptr<AccessPoint>
WiFiManager::createAccessPointObject() {
  return std::make_unique<AccessPoint>(getUniqueName());
}

std::unique_ptr<IEntity>
WiFiManager::onGetConnection() {
  if (hasConnection()) {
    return createConnectionObject();
  } else {
    return std::make_unique<Status>(StatusCode::NotFound, "The connection doesn't exist.");
  }
}

std::unique_ptr<IEntity>
WiFiManager::onCreateConnection(const Models::Connection& connection) {
  auto result = connect(connection.getNetworkSsid(), connection.getNetworkPassword());
  if (!result.isOk()) {
    return std::make_unique<Status>(StatusCode::InternalServerError,
      "Unable to create the connection.", std::move(result));
  }
  connectionController->sendEvent(EventType::Created, createConnectionObject());
  return std::make_unique<Status>(StatusCode::Created, "The connection was created.");
}

std::unique_ptr<IEntity>
WiFiManager::onDeleteConnection() {
  auto result = disconnect();
  if (!result.isOk()) {
    return std::make_unique<Status>(StatusCode::InternalServerError,
      "Unable to delete the connection.", std::move(result));
  }
  connectionController->sendEvent(EventType::Deleted);
  return std::make_unique<Status>(StatusCode::NoContent, "The connection was deleted.");
}

std::unique_ptr<IEntity>
WiFiManager::onGetAccessPoint() {
  if (hasAccessPoint()) {
    return createAccessPointObject();
  } else {
    return std::make_unique<Status>(StatusCode::NotFound, "The access point doesn't exist.");
  }
}

void
WiFiManager::onConnected() {
  if (hasConnection()) {
    if (MDNS.begin(getUniqueName().c_str())) {
      MDNS.addService("http", "tcp", 80);
    }
    isConnectedInternal = true;
    connectionController->sendEvent(EventType::Updated, createConnectionObject());
  }
}

void
WiFiManager::onDisconnected() {
  if (hasConnection() && isConnectedInternal) {
    isConnectedInternal = false;
    connectionController->sendEvent(EventType::Updated, createConnectionObject());
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
