// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_DISPLAY_HPP
#define SERVICES_DISPLAY_HPP

#include "Core/ILoopedService.hpp"
#include "Core/IMessageQueue.hpp"
#include "Core/QueueResourceClient.hpp"
#include "Core/QueueResourceController.hpp"
#include "Models/Color.hpp"
#include "Models/Connection.hpp"
#include "Models/AccessPoint.hpp"
#include "Services/Settings.hpp"

#include <memory>

class Adafruit_NeoPixel;

namespace Services {

class Display : public Core::ILoopedService  {
  TYPE_PTRS(Display)
  public:
    Display(Services::Settings::Shared settings,
            Core::IMessageQueue::Shared messageQueue);

    // From ILoopedService
    virtual void loop() override;

  private:
    Services::Settings::Shared          settings;
    Core::IMessageQueue::Shared         messageQueue;
    std::unique_ptr<Adafruit_NeoPixel>  pixels;

    Core::QueueResourceController<Models::Color>::Shared colorController;
    Core::QueueResourceClient<Models::Connection>::Unique connectionClient;
    Core::QueueResourceClient<Models::AccessPoint>::Unique accessPointClient;

    // Color
    Models::Color color;

    // WiFi state
    bool hasAccessPoint;
    bool isConnected;

    void colorWipe(uint32_t color);
    void updateDisplay();

    // Color controller
    Core::ActionResult::Unique onGetColor();
    Core::StatusResult::Unique onUpdateColor(const Models::Color& color);

    // Connection events
    void onConnectionGetStatusResponse(const Core::StatusResult& status);
    void onConnectionGetObjectResponse(const Models::Connection& connection);
    void onConnectionCreateNotification(const Models::Connection& connection);
    void onConnectionUpdateNotification(const Models::Connection& connection);
    void onConnectionDeleteNotification();

    // Access point events
    void onAccessPointGetStatusResponse(const Core::StatusResult& status);
    void onAccessPointGetObjectResponse(const Models::AccessPoint& accessPoint);
    void onAccessPointCreateNotification(const Models::AccessPoint& accessPoint);
    void onAccessPointDeleteNotification();
};

}

#endif /* end of include guard: SERVICES_DISPLAY_HPP */
