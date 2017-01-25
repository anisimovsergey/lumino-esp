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
#include "Models/Settings.hpp"
#include "Services/Settings.hpp"

namespace Services {

class SettingsController : public Core::ILoopedService  {
  TYPE_PTRS(SettingsController)
  public:
    SettingsController(Services::Settings::Shared settings,
                       Core::IMessageQueue::Shared messageQueue);

    // From ILoopedService
    virtual void loop() override;

  private:
    Services::Settings::Shared          settings;
    Core::IMessageQueue::Shared         messageQueue;
    Core::QueueResourceController<Models::Settings>::Unique controller;

    Core::ActionResult::Unique onGetSettings();
    Core::StatusResult::Unique onUpdateSettings(const Models::Settings& model);
};

}

#endif /* end of include guard: SETTINGS_CONTROLLER_HPP */
