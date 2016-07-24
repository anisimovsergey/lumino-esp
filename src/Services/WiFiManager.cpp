#include "WiFiManager.hpp"
#include "Core/Logger.hpp"
#include "Core/Utils.hpp"

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

  auto onGetConnectionHandler = std::make_shared<GetMessageReceiver>(ConnectionResource,
    std::bind(&WiFiManager::onGetConnection, this, _1));
  messageQueue->addMessageReceiver(onGetConnectionHandler);
  auto onCreateConnectionHandler = std::make_shared<CreateMessageReceiver<Connection>>(ConnectionResource,
    std::bind(&WiFiManager::onCreateConnection, this, _1, _2));
  messageQueue->addMessageReceiver(onCreateConnectionHandler);
  auto onDeleteConnectionHandler = std::make_shared<DeleteMessageReceiver>(ConnectionResource,
    std::bind(&WiFiManager::onDeleteConnection, this, _1));
  messageQueue->addMessageReceiver(onDeleteConnectionHandler);

  connectedEventHandler = WiFi.onStationModeGotIP([=](const WiFiEventStationModeGotIP&) {
    Logger::message("connected..");
    onConnected();
  });

  disconnectedEventHandler = WiFi.onStationModeDisconnected([=](const WiFiEventStationModeDisconnected&) {
    Logger::message("disconnected..");
    onDisconnected();
  });
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

std::unique_ptr<Core::StatusResult>
WiFiManager::onGetConnection(std::shared_ptr<Core::Request> request) {

  std::unique_ptr<Core::IActionResult> actionResult;
  if (hasConnection()) {
    actionResult = ObjectResult::OK(createConnection());
  } else {
    actionResult = StatusResult::NotFound("The connection doesn't exist.");
  }

  messageQueue->replyTo(*request, std::move(actionResult), SenderId);
  return StatusResult::Accepted();
}

std::unique_ptr<Core::StatusResult>
WiFiManager::onCreateConnection(std::shared_ptr<Core::Request> request,
  const Models::Connection& connection) {

  std::unique_ptr<Core::IActionResult> actionResult;
  auto result = connect(connection.getNetworkSsid(), connection.getNetworkPassword());
  if (result->isOk()) {
    auto objectResult = ObjectResult::Created(createConnectionObject());
    controller->sendCreateNotification(std::move(objectResult));
    result = StatusResult::Created("the connection was created.");
  } else {
    actionResult = StatusResult::InternalServerError("Unable to create the connection.",
      std::move(result));
  }
  messageQueue->sendCreateResponse(std::move(result));
  return StatusResult::Accepted();
}

std::unique_ptr<Core::StatusResult>
WiFiManager::onDeleteConnection(std::shared_ptr<Core::Request> request) {

  std::unique_ptr<Core::IActionResult> actionResult;
  auto result = disconnect();
  if (result->isOk()) {
    actionResult = StatusResult::NoContent("The connection was deleted.");
  } else {
    actionResult = StatusResult::InternalServerError("Unable to delete the connection.",
        std::move(result));
  }

  auto notification = Notification::makeShared(
    ActionType::Delete,
    ConnectionResource,
    std::move(actionResult)
  );
  messageQueue->broadcast(SenderId, notification);
  return StatusResult::Accepted();
}

void
WiFiManager::onConnected() {
  if (hasConnection()) {
    auto notification = Notification::makeShared(
      ActionType::Update,
      ConnectionResource,
      ObjectResult::OK(createConnection())
    );
    messageQueue->broadcast(SenderId, notification);
  }
}

void
WiFiManager::onDisconnected() {
  if (hasConnection()) {
    auto notification = Notification::makeShared(
      ActionType::Update,
      ConnectionResource,
      ObjectResult::OK(createConnection())
    );
    messageQueue->broadcast(SenderId, notification);
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
