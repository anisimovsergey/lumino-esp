// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_DISPLAY_HPP
#define SERVICES_DISPLAY_HPP

#include "Core/ILoopedService.hpp"
#include "Core/IMessageQueue.hpp"
#include "Models/Connection.hpp"
#include "Core/QueueResourceClient.hpp"

#include <memory>

class Adafruit_NeoPixel;

namespace Services {

class Display : public Core::ILoopedService  {
  TYPE_PTRS(Display)
  public:
    Display(Core::IMessageQueue::Shared messageQueue);

    // From ILoopedService
    virtual void loop() override;

  private:
    Core::IMessageQueue::Shared messageQueue;
    std::unique_ptr<Adafruit_NeoPixel> pixels;
    Core::QueueResourceClient<Models::Connection>::Unique client;

    void colorWipe(uint32_t color);
    void updateConnectionStatus(const Models::Connection& connection);

    // Events
    void onConnectionGetStatusResponse(const Core::StatusResult& status);
    void onConnectionGetObjectResponse(const Models::Connection& connection);
    void onConnectionCreateNotification(const Models::Connection& connection);
    void onConnectionUpdateNotification(const Models::Connection& connection);
    void onConnectionDeleteNotification();
};

}

#endif /* end of include guard: SERVICES_DISPLAY_HPP */
