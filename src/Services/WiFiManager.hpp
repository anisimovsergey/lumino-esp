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
#include <Ticker.h>

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
    Ticker                            disconnectTimer;
    bool                              isConnectedInternal;
    Core::QueueResourceController<Models::Connection>::Shared controller;

    // Event handlers
    WiFiEventHandler                  connectedEventHandler;
    WiFiEventHandler                  disconnectedEventHandler;
    WiFiEventHandler                  clientConnectedEventHandler;
    WiFiEventHandler                  clientDisconnectedEventHandler;

    bool        hasConnection() const;
    std::string getNetwork() const;
    bool        isConnected() const;

    Models::Connection::Unique createConnectionObject();
    Core::StatusResult::Unique connect(std::string network, std::string password);
    Core::StatusResult::Unique disconnect();

    // Message handling
    Core::ActionResult::Unique onGetConnection();
    Core::StatusResult::Unique onCreateConnection(const Models::Connection& connection);
    Core::StatusResult::Unique onDeleteConnection();

    // Events handling
    void onConnected();
    void onDisconnected();
    void onClientConnected();
    void onClientDisconnected();

    void startSoftAP();
    void stopSoftAP();

    // Access point automatic shutdown
    static void onDisconnectStatic(WiFiManager* manager);

    void startDisconnectTimer();
    void stopDisconnectTimer();
    void onDisconnectTimeout();
  };
}

#endif /* end of include guard: SERVICES_WIFIMANAGER_HPP */
