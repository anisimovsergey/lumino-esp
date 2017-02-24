// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SETTINGS_CONTROLLER_HPP
#define SETTINGS_CONTROLLER_HPP

#include "Messaging/IMessageQueue.hpp"
#include "Models/Settings.hpp"
#include "Models/Color.hpp"

namespace Services {

class SettingsController {
  public:
    SettingsController(Messaging::IMessageQueue& messageQueue);

  private:
    Messaging::IMessageQueue&            messageQueue;

    std::string     getDeviceName() const;
    void            setDeviceName(std::string name);

    Models::Color   getColor() const;
    void            setColor(const Models::Color& color);

    std::unique_ptr<Messaging::QueueResourceController>  settingsController;
    std::unique_ptr<Messaging::QueueResourceController>  colorController;

    std::unique_ptr<Core::IEntity> onGetSettings();
    std::unique_ptr<Core::IEntity> onUpdateSettings(const Models::Settings& model);

    std::unique_ptr<Core::IEntity> onGetColor();
    std::unique_ptr<Core::IEntity> onUpdateColor(const Models::Color& model);
};

}

#endif /* end of include guard: SETTINGS_CONTROLLER_HPP */
