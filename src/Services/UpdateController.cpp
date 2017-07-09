#include "UpdateController.hpp"

#include <ArduinoOTA.h>

using namespace Core;
using namespace Messaging;
using namespace Services;
using namespace Models;

namespace {
  const char* SenderId = "Updater";
}

UpdateController::UpdateController(IMessageQueue& messageQueue, ILogger& logger) :
  messageQueue(messageQueue), logger(logger) {

  connectionClient = messageQueue.createClient(SenderId, Connection::TypeId());
  connectionClient->addOnEvent(EventType::Updated, [=](const Models::Connection& connection) {
    onConnectionUpdated(connection);
  });
}

void
UpdateController::idle() {
  ArduinoOTA.handle();
}

void
UpdateController::start() {
  logger.message("OTA started...");
  ArduinoOTA.begin();
}

void
UpdateController::onConnectionUpdated(const Models::Connection& connection) {
  if (connection.getIsConnected()) {
    start();
  }
}
