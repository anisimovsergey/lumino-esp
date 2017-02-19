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
  public:
    ColorController(Services::Settings& settings,
                    Messaging::IMessageQueue& messageQueue);

    virtual void idle() override;

  private:
    Services::Settings& settings;
    Messaging::IMessageQueue& messageQueue;
    std::unique_ptr<Messaging::QueueResourceController> controller;

    std::unique_ptr<Core::IEntity> onGetColor();
    std::unique_ptr<Core::IEntity> onUpdateColor(const Models::Color& model);
};

}

#endif /* end of include guard: SETTINGS_CONTROLLER_HPP */
