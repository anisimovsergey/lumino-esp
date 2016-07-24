// Copyright Sergey Anisimov 2016-2017

// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_WIFIMANAGER_HPP
#define SERVICES_WIFIMANAGER_HPP

#include "IWiFiManager.hpp"
#include "IDisplay.hpp"
#include "Core/ILoopedService.hpp"
#include "Core/IMessageQueue.hpp"
#include "Core/QueueResourceController.hpp"
#include "Models/Connection.hpp"

#include <DNSServer.h>
#include <ESP8266WiFi.h>

#include <memory>

namespace Services {
  class WiFiManager : public IWiFiManager, public Core::ILoopedService {
  public:
    WiFiManager(std::shared_ptr<Core::IMessageQueue> messageQueue);
    ~WiFiManager();

    void   start();

    String getDeviceName() const override;
    bool   hasConnection() const override;
    String getNetwork() const override;
    bool   isConnected() const override;

    Core::StatusResult::Unique connect(String network, String password) override;
    Core::StatusResult::Unique disconnect() override;
    void   loop() override;

  private:
    std::unique_ptr<DNSServer> dnsServer;
    std::shared_ptr<Core::IMessageQueue> messageQueue;
    WiFiEventHandler connectedEventHandler;
    WiFiEventHandler disconnectedEventHandler;
    Core::QueueResourceController<Models::Connection>::Shared controller;
    String deviceName;

    Models::Connection::Unique createConnectionObject();

    // Message handling
    Core::IActionResult::Unique onGetConnection();
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
