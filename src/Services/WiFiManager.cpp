#include "WiFiManager.hpp"
#include "Core/Logger.hpp"
#include "Core/Utils.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Models;
using namespace Services;
using namespace std::placeholders;

static const String SenderId = "WiFiManager";
static const String ConnectionResource = "/connection";

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

  disconnected = WiFi.onStationModeDisconnected([=](const WiFiEventStationModeDisconnected&) {
    auto notification = std::make_shared<Notification>(
      ActionType::Update,
      ConnectionResource,
      ObjectResult::OK(
        make_unique<Connection>(
          getNetwork(),
          isConnected()
        )
      )
    );
    messageQueue->broadcast(SenderId, notification);
  });
  gotIP = WiFi.onStationModeGotIP([=](const WiFiEventStationModeGotIP&) {
    Logger::message("Creating notification");
    auto notification = std::make_shared<Notification>(
      ActionType::Update,
      ConnectionResource,
      ObjectResult::OK(
        make_unique<Connection>(
          getNetwork(),
          isConnected()
        )
      )
    );
    Logger::message("Sending notification");
    messageQueue->broadcast(SenderId, notification);
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
  auto ipAddress = WiFi.softAP(deviceName.c_str());
  dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer->start(53, "*", ipAddress);
}

void
WiFiManager::stopSoftAP() {
  WiFi.softAPdisconnect();
}

std::unique_ptr<Core::StatusResult>
WiFiManager::onGetConnection(std::shared_ptr<Core::Request> request) {

  std::unique_ptr<Core::IActionResult> actionResult;
  if (hasConnection()) {
    actionResult = ObjectResult::OK(
      make_unique<Connection>(
        getNetwork(),
        isConnected()
      ));
  } else {
    actionResult = StatusResult::NotFound("The connection doesn't exist.");
  }

  auto notification = std::make_shared<Notification>(
    ActionType::Get,
    ConnectionResource,
    std::move(actionResult)
  );
  messageQueue->notify(*request, notification);
  return StatusResult::Accepted();
}

std::unique_ptr<Core::StatusResult>
WiFiManager::onCreateConnection(std::shared_ptr<Core::Request> request,
  const Models::Connection& connection) {

  std::unique_ptr<Core::IActionResult> actionResult;
  auto result = connect(connection.getNetworkSsid(), connection.getNetworkPassword());
  if (result->isOk()) {
    actionResult = ObjectResult::Created(
      make_unique<Connection>(
        getNetwork(),
        isConnected()
    ));
  } else {
    actionResult = StatusResult::InternalServerError("Unable to create the connection.",
      std::move(result));
  }

  auto notification = std::make_shared<Notification>(
    ActionType::Create,
    ConnectionResource,
    std::move(actionResult)
  );
  messageQueue->broadcast(SenderId, notification);
  return StatusResult::Accepted();
}

std::unique_ptr<Core::StatusResult>
WiFiManager::onDeleteConnection(std::shared_ptr<Core::Request> request) {

  auto result = disconnect();
  if (result->isOk()) {
    result = StatusResult::NoContent("Connection was deleted.");
  } else {
    result = StatusResult::InternalServerError("Unable to delete the connection.",
      std::move(result));
  }

  auto notification = std::make_shared<Notification>(
    ActionType::Delete,
    ConnectionResource,
    std::move(result)
  );
  messageQueue->broadcast(SenderId, notification);
  return StatusResult::Accepted();
}
