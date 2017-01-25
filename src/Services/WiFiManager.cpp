#include "WiFiManager.hpp"
#include "Core/Memory.hpp"
#include "Core/Format.hpp"
#include "Models/Connection.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Models;
using namespace Messaging;
using namespace Services;

using namespace std::placeholders;

WiFiManager::WiFiManager(
  std::shared_ptr<const Settings> settings,
  IMessageQueue::Shared messageQueue) :
  settings(settings),
  messageQueue(messageQueue) {

  dnsServer = std::move(Core::makeUnique<DNSServer>());
  isConnectedInternal = false;

  auto controller = messageQueue->createController(Connection::TypeId());

  controller->addOnRequest("get",
    std::bind(&WiFiManager::onGetConnection, this));
  controller->addOnRequest<Connection>("create",
    std::bind(&WiFiManager::onCreateConnection, this, _1));
  controller->addOnRequest("delete",
    std::bind(&WiFiManager::onDeleteConnection, this));

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
  WiFi.hostname(settings->getDeviceName().c_str());
  startSoftAP();
  startDisconnectTimer();
}

bool
WiFiManager::hasConnection() const {
  return (WiFi.SSID().length() > 0);
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
WiFiManager::idle() {
  dnsServer->processNextRequest();
}

Models::Connection::Unique
WiFiManager::createConnectionObject() {
  return Connection::makeUnique(getNetwork(), isConnected());
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

  controller->sendEvent("created",createConnectionObject());
  return Status::makeUnique(StatusCode::Created, "The connection was created.");
}

Core::IEntity::Unique
WiFiManager::onDeleteConnection() {

  auto result = disconnect();
  if (!result.isOk()) {
    return Status::makeUnique(StatusCode::InternalServerError,
      "Unable to delete the connection.", std::move(result));
  }

  controller->sendEvent("deleted");
  return Status::makeUnique(StatusCode::NoContent, "The connection was deleted.");
}

void
WiFiManager::onConnected() {
  if (hasConnection() && !isConnectedInternal) {
    isConnectedInternal = true;
    controller->sendEvent("updated", createConnectionObject());
  }
}

void
WiFiManager::onDisconnected() {
  if (hasConnection() && isConnectedInternal) {
    isConnectedInternal = false;
    controller->sendEvent("updated", createConnectionObject());
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
WiFiManager::startSoftAP() {
  WiFi.softAP(settings->getDeviceName().c_str());
  dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer->start(53, "*", WiFi.softAPIP());
}

void
WiFiManager::stopSoftAP() {
  dnsServer->stop();
  WiFi.softAPdisconnect();
  WiFi.mode(WIFI_STA);
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
