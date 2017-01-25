#include "SettingsController.hpp"

#include "Core/ObjectResult.hpp"

using namespace Core;
using namespace Services;
using namespace std::placeholders;

namespace {
  const char* ControllerId = "Settings";
}

SettingsController::SettingsController(
  Services::Settings::Shared settings,
  Core::IMessageQueue::Shared messageQueue) :
  settings(settings),
  messageQueue(messageQueue) {

  auto queueController = messageQueue->createController(ControllerId);
  controller = QueueResourceController<Models::Settings>::makeUnique(queueController);
  controller->setOnGetRequestHandler(std::bind(&SettingsController::onGetSettings, this));
  controller->setOnUpdateRequestHandler(std::bind(&SettingsController::onUpdateSettings, this, _1));
}

void
SettingsController::loop() {
}

Core::ActionResult::Unique
SettingsController::onGetSettings() {
  auto model = Models::Settings::makeUnique(settings->getDeviceName());
  return ObjectResult::makeUnique(StatusCode::OK, std::move(model));
}

Core::StatusResult::Unique
SettingsController::onUpdateSettings(const Models::Settings& model) {
  settings->setDeviceName(model.getDeviceName());
  controller->sendUpdateNotification(Models::Settings::makeUnique(model));
  return StatusResult::OK();
}
