// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SETTINGS_CONTROLLER_HPP
#define SETTINGS_CONTROLLER_HPP

#include "Core/ILoopedService.hpp"
#include "Core/IMessageQueue.hpp"
#include "Core/QueueResourceController.hpp"
#include "Models/Color.hpp"
#include "Services/Settings.hpp"

namespace Services {

class ColorController : public Core::ILoopedService  {
  TYPE_PTRS(ColorController)
  public:
    ColorController(Services::Settings::Shared settings,
                       Core::IMessageQueue::Shared messageQueue);

    // From ILoopedService
    virtual void loop() override;

  private:
    Services::Settings::Shared          settings;
    Core::IMessageQueue::Shared         messageQueue;
    Core::QueueResourceController<Models::Color>::Unique controller;

    Core::ActionResult::Unique onGetColor();
    Core::StatusResult::Unique onUpdateColor(const Models::Color& model);
};

}

#endif /* end of include guard: SETTINGS_CONTROLLER_HPP */
