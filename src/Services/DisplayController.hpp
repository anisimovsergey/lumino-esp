// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_DISPLAY_CONTROLLER_HPP
#define SERVICES_DISPLAY_CONTROLLER_HPP

#include "Core/IService.hpp"
#include "Messaging/IMessageQueue.hpp"
#include "Messaging/QueueResourceClient.hpp"
#include "Models/Color.hpp"
#include "Models/Connection.hpp"
#include "Models/AccessPoint.hpp"

class Adafruit_NeoPixel;

namespace Services {

class DisplayController : public Core::IService  {
  TYPE_PTRS(DisplayController)
  public:
    DisplayController(Messaging::IMessageQueue::Shared messageQueue);

    // From ILoopedService
    virtual void idle() override;

  private:
    Messaging::IMessageQueue::Shared messageQueue;
    Messaging::QueueResourceClient::Unique client;
    std::unique_ptr<Adafruit_NeoPixel, void (*)(Adafruit_NeoPixel *)> pixels;

    Messaging::QueueResourceClient::Shared        colorClient;
    Messaging::QueueResourceClient::Shared   connectionClient;
    Messaging::QueueResourceClient::Shared  accessPointClient;

    Models::Color color;
    bool hasAccessPoint;
    bool isConnected;

    void colorWipe(uint32_t color);
    void updateDisplay();

    // Color events
    void onColorGetObjectResponse(const Models::Color& color);
    void onColorUpdateNotification(const Models::Color& color);

    // Connection events
    void onConnectionGetStatusResponse(const Core::Status& status);
    void onConnectionGetObjectResponse(const Models::Connection& connection);
    void onConnectionCreateNotification(const Models::Connection& connection);
    void onConnectionUpdateNotification(const Models::Connection& connection);
    void onConnectionDeleteNotification();

    // Access point events
    void onAccessPointGetStatusResponse(const Core::Status& status);
    void onAccessPointGetObjectResponse(const Models::AccessPoint& accessPoint);
    void onAccessPointCreateNotification(const Models::AccessPoint& accessPoint);
    void onAccessPointDeleteNotification();
};

}

#endif /* end of include guard: SERVICES_DISPLAY_CONTROLLER_HPP */
