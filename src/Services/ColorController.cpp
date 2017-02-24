#include "ColorController.hpp"

using namespace Core;
using namespace Services;
using namespace Models;

ColorController::ColorController(Services::Settings& settings,
                                 Messaging::IMessageQueue& messageQueue) :
  settings(settings),
  messageQueue(messageQueue) {

  controller = messageQueue.createController(Color::TypeId());
  controller->addOnRequest("get", [=](){ return onGetColor(); });
  controller->addOnRequest("update", [=](const Models::Color& model){
    return onUpdateColor(model);
  });
}

std::unique_ptr<Core::IEntity>
ColorController::onGetColor() {
  return std::make_unique<Models::Color>(settings.getColor());
}

std::unique_ptr<Core::IEntity>
ColorController::onUpdateColor(const Models::Color& model) {
  settings.setColor(model);
  controller->sendEvent("updated", std::make_unique<Models::Color>(model));
  return std::make_unique<Status>(Status::OK);
}
