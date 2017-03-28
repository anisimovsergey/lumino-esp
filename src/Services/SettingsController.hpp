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

#include <Ticker.h>

namespace Services {

class SettingsController {
  public:
    SettingsController(
      Messaging::IMessageQueue& messageQueue
    );

  private:
    Messaging::IMessageQueue&   messageQueue;
    Ticker                      commitTimer;

    std::string     getDeviceName() const;
    bool            setDeviceName(std::string name);

    Models::Color   getColor() const;
    bool            setColor(const Models::Color& color);

    std::unique_ptr<Messaging::QueueResourceController>  settingsController;
    std::unique_ptr<Messaging::QueueResourceController>  colorController;

    std::unique_ptr<Core::IEntity> onGetSettings();
    std::unique_ptr<Core::IEntity> onUpdateSettings(const Models::Settings& Settings);

    std::unique_ptr<Core::IEntity> onGetColor();
    std::unique_ptr<Core::IEntity> onUpdateColor(const Models::Color& color);

    // Delayed commit
    static void onCommitStatic(SettingsController* manager);
    void startCommitTimer();
    void onCommitTimeout();
};

}

#endif /* end of include guard: SETTINGS_CONTROLLER_HPP */
