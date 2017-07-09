// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Lumino
// https://github.com/anisimovsergey/lumino-esp

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Core/Logger.hpp"
#include "Messaging/MessageQueue.hpp"
#include "Services/DisplayController.hpp"
#include "Services/SettingsController.hpp"
#include "Services/UpdateController.hpp"
#include "Services/WiFiManager.hpp"
#include "Services/WiFiScanner.hpp"
#include "Services/WebServerAsync.hpp"
#include "Serialization/ContextFactory.hpp"
#include "Serialization/SerializationService.hpp"

#include <memory>

class Application {
  private:
    std::unique_ptr<Core::Logger>                         logger;
    std::unique_ptr<Messaging::MessageQueue>              messageQueue;
    std::unique_ptr<Services::DisplayController>          display;
    std::unique_ptr<Services::SettingsController>         settings;
    std::unique_ptr<Services::UpdateController>           updater;
    std::unique_ptr<Services::WiFiManager>                wifiManager;
    std::unique_ptr<Services::WiFiScanner>                wifiScanner;
    std::unique_ptr<Services::WebServerAsync>             webServerAsync;
    std::unique_ptr<Serialization::ContextFactory>        contextFactory;
    std::unique_ptr<Serialization::SerializationService>  serializer;

  public:
    void setup();
    void loop();

  private:
    void createServices();
    void registerSerializers();
};

#endif /* end of include guard: APPLICATION_HPP */
