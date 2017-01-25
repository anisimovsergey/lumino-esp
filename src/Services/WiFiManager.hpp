// Copyright Sergey Anisimov 2016-2017

// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_WIFIMANAGER_HPP
#define SERVICES_WIFIMANAGER_HPP

#include "Core/IService.hpp"
#include "Messaging/IMessageQueue.hpp"
#include "Messaging/QueueResourceController.hpp"
#include "Models/Connection.hpp"
#include "Settings.hpp"

#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>

#include <memory>

namespace Services {
  class WiFiManager : public Core::IService {
    TYPE_PTRS(WiFiManager)
  public:
    WiFiManager(
      std::shared_ptr<const Settings> settings,
      Messaging::IMessageQueue::Shared messageQueue);

    void   start();
    void   idle() override;

  private:
    std::shared_ptr<const Settings>   settings;
    Messaging::IMessageQueue::Shared  messageQueue;
    std::unique_ptr<DNSServer>        dnsServer;
    Ticker                            disconnectTimer;
    bool                              isConnectedInternal;
    Messaging::QueueResourceController::Shared controller;

    // Event handlers
    WiFiEventHandler                  connectedEventHandler;
    WiFiEventHandler                  disconnectedEventHandler;
    WiFiEventHandler                  clientConnectedEventHandler;
    WiFiEventHandler                  clientDisconnectedEventHandler;

    bool        hasConnection() const;
    std::string getNetwork() const;
    bool        isConnected() const;

    Models::Connection::Unique createConnectionObject();
    Core::Status connect(std::string network, std::string password);
    Core::Status disconnect();

    // Message handling
    Core::IEntity::Unique onGetConnection();
    Core::IEntity::Unique onCreateConnection(const Models::Connection& connection);
    Core::IEntity::Unique onDeleteConnection();

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
