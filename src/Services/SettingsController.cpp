#include "SettingsController.hpp"

#include "Core/Memory.hpp"

using namespace Core;
using namespace Services;

SettingsController::SettingsController(
  Services::Settings& settings,
  Messaging::IMessageQueue& messageQueue) :
  settings(settings),
  messageQueue(messageQueue) {

  controller = messageQueue.createController(Models::Settings::TypeId());
  controller->addOnRequest("get", [=]() {
    return onGetSettings();
  });
  controller->addOnRequest("update", [=](const Models::Settings& model) {
    return onUpdateSettings(model);
  });
}

std::unique_ptr<Core::IEntity>
SettingsController::onGetSettings() {
  return std::make_unique<Models::Settings>(settings.getDeviceName());
}

std::unique_ptr<IEntity>
SettingsController::onUpdateSettings(const Models::Settings& model) {
  settings.setDeviceName(model.getDeviceName());
  controller->sendEvent("updated", std::make_unique<Models::Settings>(model));
  return std::make_unique<Status>(Status::OK);
}
