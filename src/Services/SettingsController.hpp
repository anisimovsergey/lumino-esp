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
#include "Models/Settings.hpp"
#include "Services/Settings.hpp"

namespace Services {

class SettingsController : public Core::IService  {
  TYPE_PTRS(SettingsController)
  public:
    SettingsController(Services::Settings::Shared settings,
                       Messaging::IMessageQueue::Shared messageQueue);

    // From ILoopedService
    virtual void idle() override;

  private:
    Services::Settings::Shared                  settings;
    Messaging::IMessageQueue::Shared            messageQueue;
    Messaging::QueueResourceController::Shared  controller;

    Core::IEntity::Unique onGetSettings();
    Core::IEntity::Unique onUpdateSettings(const Models::Settings& model);
};

}

#endif /* end of include guard: SETTINGS_CONTROLLER_HPP */
