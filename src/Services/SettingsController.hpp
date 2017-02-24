// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SETTINGS_CONTROLLER_HPP
#define SETTINGS_CONTROLLER_HPP

#include "Messaging/IMessageQueue.hpp"
#include "Models/Settings.hpp"
#include "Services/Settings.hpp"

namespace Services {

class SettingsController {
  public:
    SettingsController(Services::Settings& settings,
                       Messaging::IMessageQueue& messageQueue);

  private:
    Services::Settings&                  settings;
    Messaging::IMessageQueue&            messageQueue;
    std::unique_ptr<Messaging::QueueResourceController>  controller;

    std::unique_ptr<Core::IEntity> onGetSettings();
    std::unique_ptr<Core::IEntity> onUpdateSettings(const Models::Settings& model);
};

}

#endif /* end of include guard: SETTINGS_CONTROLLER_HPP */
