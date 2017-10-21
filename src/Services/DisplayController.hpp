// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Lumino
// https://github.com/anisimovsergey/lumino-esp

#ifndef SERVICES_DISPLAY_CONTROLLER_HPP
#define SERVICES_DISPLAY_CONTROLLER_HPP

#include "Core/ILogger.hpp"
#include "Messaging/IMessageQueue.hpp"
#include "Models/Settings.hpp"
#include "Models/Color.hpp"
#include "Models/Connection.hpp"
#include "Models/AccessPoint.hpp"

class Adafruit_NeoPixel;

namespace Services {

class DisplayController {
  public:
    DisplayController(
      Messaging::IMessageQueue& messageQueue,
      Core::ILogger& logger
    );

  private:
    Messaging::IMessageQueue& messageQueue;
    Core::ILogger&            logger;
    std::unique_ptr<Adafruit_NeoPixel, void (*)(Adafruit_NeoPixel *)> pixels;

    std::unique_ptr<Messaging::QueueResourceClient> settingsClient;
    std::unique_ptr<Messaging::QueueResourceClient> colorClient;
    std::unique_ptr<Messaging::QueueResourceClient> connectionClient;
    std::unique_ptr<Messaging::QueueResourceClient> accessPointClient;

    bool isOn;
    Models::Color color;
    bool hasAccessPoint;
    bool isConnected;

    void colorWipe(uint32_t color);
    void updateDisplay();

    // Settings events
    void onSettingsCreated(const Models::Settings& settings);
    void onSettingsUpdated(const Models::Settings& settings);

    // Color events
    void onColorCreated(const Models::Color& color);
    void onColorUpdated(const Models::Color& color);

    // Connection events
    void onConnectionCreated(const Models::Connection& connection);
    void onConnectionUpdated(const Models::Connection& connection);
    void onConnectionDeleted();

    // Access point events
    void onAccessPointCreated(const Models::AccessPoint& accessPoint);
    void onAccessPointDeleted();
};

}

#endif /* end of include guard: SERVICES_DISPLAY_CONTROLLER_HPP */
