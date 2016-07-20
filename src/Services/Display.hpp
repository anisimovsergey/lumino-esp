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
    DisplaySign currentSign;
    std::unique_ptr<Adafruit_NeoPixel> pixels;
    void colorWipe(uint32_t color);

    void onBroadcast(Core::Notification::Shared notification);
};

}

#endif /* end of include guard: SERVICES_DISPLAY_HPP */
