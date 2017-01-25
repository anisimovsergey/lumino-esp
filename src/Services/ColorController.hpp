// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SETTINGS_CONTROLLER_HPP
#define SETTINGS_CONTROLLER_HPP

#include "Core/IService.hpp"
#include "Messaging/IMessageQueue.hpp"
#include "Messaging/QueueResourceController.hpp"
#include "Models/Color.hpp"
#include "Services/Settings.hpp"

namespace Services {

class ColorController : public Core::IService  {
  TYPE_PTRS(ColorController)
  public:
    ColorController(Services::Settings::Shared settings,
                    Messaging::IMessageQueue::Shared messageQueue);

    // From ILoopedService
    virtual void idle() override;

  private:
    Services::Settings::Shared                  settings;
    Messaging::IMessageQueue::Shared            messageQueue;
    Messaging::QueueResourceController::Shared  controller;

    Core::IEntity::Unique onGetColor();
    Core::IEntity::Unique onUpdateColor(const Models::Color& model);
};

}

#endif /* end of include guard: SETTINGS_CONTROLLER_HPP */
