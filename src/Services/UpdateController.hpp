// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Lumino
// https://github.com/anisimovsergey/lumino-esp

#ifndef UPDATE_CONTROLLER_HPP
#define UPDATE_CONTROLLER_HPP

#include "Messaging/IMessageQueue.hpp"
#include "Models/Connection.hpp"
#include "Core/ILogger.hpp"

namespace Services {

class UpdateController {
  public:
    UpdateController(
      Messaging::IMessageQueue& messageQueue,
      Core::ILogger& logger
    );

    void   idle();

  private:
    Messaging::IMessageQueue&   messageQueue;
    Core::ILogger&              logger;
    std::unique_ptr<Messaging::QueueResourceClient> connectionClient;

    void   start();
    void    onConnectionUpdated(const Models::Connection& connection);
};

}

#endif /* end of include guard: UPDATE_CONTROLLER_HPP */
