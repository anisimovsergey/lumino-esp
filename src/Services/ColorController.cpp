#include "ColorController.hpp"

#include "Core/ObjectResult.hpp"

using namespace Core;
using namespace Services;
using namespace std::placeholders;

namespace {
  const char* ControllerId = "Color";
}

ColorController::ColorController(
  Services::Settings::Shared settings,
  Core::IMessageQueue::Shared messageQueue) :
  settings(settings),
  messageQueue(messageQueue) {

  auto queueController = messageQueue->createController(ControllerId);
  controller = QueueResourceController<Models::Color>::makeUnique(queueController);
  controller->setOnGetRequestHandler(std::bind(&ColorController::onGetColor, this));
  controller->setOnUpdateRequestHandler(std::bind(&ColorController::onUpdateColor, this, _1));
}

void
ColorController::loop() {
}

Core::ActionResult::Unique
ColorController::onGetColor() {
  auto model = Models::Color::makeUnique(settings->getColor());
  return ObjectResult::makeUnique(StatusCode::OK, std::move(model));
}

Core::StatusResult::Unique
ColorController::onUpdateColor(const Models::Color& model) {
  settings->setColor(model);
  controller->sendUpdateNotification(Models::Color::makeUnique(model));
  return StatusResult::OK();
}
