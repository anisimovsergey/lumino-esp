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

#include <memory>

class Adafruit_NeoPixel;

namespace Services {

class Display : public IDisplay, public Core::ILoopedService  {
  public:
    Display(std::shared_ptr<Core::IMessageQueue> messageQueue);

    // From IDisplay
    virtual void showSigh(const DisplaySign& sign) override;

    // From ILoopedService
    virtual void loop() override;

  private:
    std::shared_ptr<Core::IMessageQueue> messageQueue;
    std::unique_ptr<Adafruit_NeoPixel> pixels;

    void colorWipe(uint32_t color);
    void updateConnectionStatus(const Models::Connection& connection);

    // Events
    void onConnectionGetNotification(const Models::Connection& connection);
    void onConnectionCreateNotification(const Models::Connection& connection);
    void onConnectionUpdateNotification(const Models::Connection& connection);
    void onConnectionDeleteNotification();
};

}

#endif /* end of include guard: SERVICES_DISPLAY_HPP */
