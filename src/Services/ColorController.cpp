#include "ColorController.hpp"

using namespace Core;
using namespace Services;
using namespace Models;

using namespace std::placeholders;

ColorController::ColorController(
  Services::Settings::Shared settings,
  Messaging::IMessageQueue::Shared messageQueue) :
  settings(settings),
  messageQueue(messageQueue) {

  controller = messageQueue->createController(Color::TypeId());
  controller->addOnRequest("get", std::bind(&ColorController::onGetColor, this));
  controller->addOnRequest<Color>("update", std::bind(&ColorController::onUpdateColor, this, _1));
}

void
ColorController::idle() {
}

Core::IEntity::Unique
ColorController::onGetColor() {
  return Models::Color::makeUnique(settings->getColor());
}

Core::IEntity::Unique
ColorController::onUpdateColor(const Models::Color& model) {
  settings->setColor(model);
  controller->sendEvent("updated", Models::Color::makeUnique(model));
  return Status::makeUnique(Status::OK);
}
