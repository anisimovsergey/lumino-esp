#include "SettingsController.hpp"

using namespace Core;
using namespace Services;

using namespace std::placeholders;

SettingsController::SettingsController(
  Services::Settings::Shared settings,
  Messaging::IMessageQueue::Shared messageQueue) :
  settings(settings),
  messageQueue(messageQueue) {

  controller = messageQueue->createController(Models::Settings::TypeId());
  controller->addOnRequest("get", std::bind(&SettingsController::onGetSettings, this));
  controller->addOnRequest<Models::Settings>("update", std::bind(&SettingsController::onUpdateSettings, this, _1));
}

void
SettingsController::idle() {
}

Core::IEntity::Unique
SettingsController::onGetSettings() {
  return Models::Settings::makeUnique(settings->getDeviceName());
}

Core::IEntity::Unique
SettingsController::onUpdateSettings(const Models::Settings& model) {
  settings->setDeviceName(model.getDeviceName());
  controller->sendEvent("updated", Models::Settings::makeUnique(model));
  return Status::makeUnique(Status::OK);
}
