// Copyright Sergey Anisimov 2016-2017

// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_WIFIMANAGER_HPP
#define SERVICES_WIFIMANAGER_HPP

#include "Core/ILoopedService.hpp"
#include "Core/IMessageQueue.hpp"
#include "Core/QueueResourceController.hpp"
#include "Models/Connection.hpp"
#include "Settings.hpp"

#include <DNSServer.h>
#include <ESP8266WiFi.h>

#include <memory>

namespace Services {
  class WiFiManager : public Core::ILoopedService {
    TYPE_PTRS(WiFiManager)
  public:
    WiFiManager(
      std::shared_ptr<const Settings> settings,
      Core::IMessageQueue::Shared messageQueue);
    ~WiFiManager();

    void   start();
    void   loop() override;

  private:
    std::shared_ptr<const Settings>   settings;
    Core::IMessageQueue::Shared       messageQueue;
    std::unique_ptr<DNSServer>        dnsServer;
    WiFiEventHandler                  connectedEventHandler;
    WiFiEventHandler                  disconnectedEventHandler;
    Core::QueueResourceController<Models::Connection>::Shared controller;

    bool        hasConnection() const;
    std::string getNetwork() const;
    bool        isConnected() const;

    Core::StatusResult::Unique connect(std::string network, std::string password);
    Core::StatusResult::Unique disconnect();

    Models::Connection::Unique createConnectionObject();

    // Message handling
    Core::ActionResult::Unique onGetConnection();
    Core::StatusResult::Unique onCreateConnection(const Models::Connection& connection);
    Core::StatusResult::Unique onDeleteConnection();

    // Events handling
    void onConnected();
    void onDisconnected();

    void startSoftAP();
    void stopSoftAP();
  };
}

#endif /* end of include guard: SERVICES_WIFIMANAGER_HPP */
