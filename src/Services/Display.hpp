// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_DISPLAY_HPP
#define SERVICES_DISPLAY_HPP

#include "IDisplay.hpp"
#include "Core/ILoopedService.hpp"
#include "Core/IMessageQueue.hpp"
#include "Models/Connection.hpp"
#include "Core/QueueResourceClient.hpp"

#include <memory>

class Adafruit_NeoPixel;

namespace Services {

class Display : public IDisplay, public Core::ILoopedService  {
  public:
    Display(std::shared_ptr<Core::IMessageQueue> messageQueue);

    // From ILoopedService
    virtual void loop() override;

  private:
    std::shared_ptr<Core::IMessageQueue> messageQueue;
    std::unique_ptr<Adafruit_NeoPixel> pixels;
    Core::QueueResourceClient<Models::Connection>::Unique client;

    void colorWipe(uint32_t color);
    void updateConnectionStatus(const Models::Connection& connection);

    // Events
    void onConnectionGetResponse(const Core::Response& result);
    void onConnectionCreateNotification(const Models::Connection& connection);
    void onConnectionUpdateNotification(const Models::Connection& connection);
    void onConnectionDeleteNotification();
};

}

#endif /* end of include guard: SERVICES_DISPLAY_HPP */
