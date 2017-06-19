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

namespace {
  static const int DISCONNECT_DELAY = 300; // 60 * 5 min
  const char* SenderId = "WiFiManager";
}

WiFiManager::WiFiManager(
  IMessageQueue& messageQueue) :
  messageQueue(messageQueue) {

  dnsServer = std::move(std::make_unique<DNSServer>());
  disconnectReason = 0;

  settingsClient = messageQueue.createClient(SenderId, Settings::TypeId());
  settingsClient->addOnEvent(EventType::Created, [=](const Models::Settings& settings) {
    onSettingsCreated(settings);
  });

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
    [=](const WiFiEventStationModeDisconnected& e) { onDisconnected(e.reason); }
  );

  clientConnectedEventHandler = WiFi.onSoftAPModeStationConnected(
    [=](const WiFiEventSoftAPModeStationConnected&) { onClientConnected(); }
  );

  clientDisconnectedEventHandler = WiFi.onSoftAPModeStationDisconnected(
    [=](const WiFiEventSoftAPModeStationDisconnected&) {  onClientDisconnected(); }
  );
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

bool
WiFiManager::isProtected() const {
  return (WiFi.psk().length() > 0);
}

Core::Status
WiFiManager::connect(std::string network, std::string password) {
  if (hasConnection()) {
    return Status(StatusCode::Conflict, "The connection already exists.");
  }
  if (WiFi.begin(network.c_str(), password.c_str()) == WL_CONNECT_FAILED) {
    return Status(StatusCode::BadRequest, "Unable to create the connection.");
  }
  return Status::OK;
}

Core::Status
WiFiManager::disconnect() {
  if (!hasConnection()) {
    return Status(StatusCode::Conflict, "The connection doesn't exist.");
  }
  WiFi.disconnect();
  disconnectReason = 0;
  return Status::OK;
}

void
WiFiManager::startService() {
  startDisconnectTimer();

  // Set DHCP host name
  WiFi.hostname(uniqueName.c_str());

  // Set access point name (SSID)
  WiFi.softAP(uniqueName.c_str());

  // Start DNS respiner
  dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer->start(53, "*", WiFi.softAPIP());

  // Sending events
  accessPointController->sendEvent(EventType::Created, createAccessPointObject());
  if (hasConnection()) {
    connectionController->sendEvent(EventType::Created, createConnectionObject());
  }
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
  return std::make_unique<Connection>(
    getNetwork(),
    isConnected(),
    isProtected(),
    WiFi.RSSI(),
    WiFi.localIP(),
    WiFi.subnetMask(),
    WiFi.gatewayIP(),
    WiFi.dnsIP(),
    disconnectReason
  );
}

std::unique_ptr<AccessPoint>
WiFiManager::createAccessPointObject() {
  return std::make_unique<AccessPoint>(uniqueName);
}

void
WiFiManager::onSettingsCreated(const Models::Settings& settings) {
  uniqueName = settings.getUniqueName();
  startService();
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
  auto result = connect(connection.getSsid(), connection.getPassword());
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
    if (MDNS.begin(uniqueName.c_str())) {
      MDNS.addService("lumino-ws", "tcp", 80);
    }
    disconnectReason = 0;
    connectionController->sendEvent(EventType::Updated, createConnectionObject());
  }
}

void
WiFiManager::onDisconnected(int reason) {
  if (hasConnection() && disconnectReason != reason) {
    disconnectReason = reason;
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
  disconnectTimer.once(DISCONNECT_DELAY, onDisconnectStatic,  this);
}

void
WiFiManager::stopDisconnectTimer() {
  disconnectTimer.detach();
}

void
WiFiManager::onDisconnectTimeout() {
  stopSoftAP();
}
