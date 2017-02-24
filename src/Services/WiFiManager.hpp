// Copyright Sergey Anisimov 2016-2017

// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_WIFIMANAGER_HPP
#define SERVICES_WIFIMANAGER_HPP

#include "Messaging/IMessageQueue.hpp"
#include "Models/Connection.hpp"
#include "Models/AccessPoint.hpp"

#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>

#include <memory>

namespace Services {

class WiFiManager {
  public:
    WiFiManager(Messaging::IMessageQueue& messageQueue);

    void   start();
    void   idle();

  private:
    Messaging::IMessageQueue&                   messageQueue;
    std::unique_ptr<DNSServer>                  dnsServer;
    Ticker                                      disconnectTimer;
    bool                                        isConnectedInternal;
    std::unique_ptr<Messaging::QueueResourceController>  connectionController;
    std::unique_ptr<Messaging::QueueResourceController>  accessPointController;

    // Event handlers
    WiFiEventHandler                  connectedEventHandler;
    WiFiEventHandler                  disconnectedEventHandler;
    WiFiEventHandler                  clientConnectedEventHandler;
    WiFiEventHandler                  clientDisconnectedEventHandler;

    std::string   getUniqueName() const;
    bool          hasConnection() const;
    bool          hasAccessPoint() const;
    std::string   getNetwork() const;
    bool          isConnected() const;

    std::unique_ptr<Models::Connection> createConnectionObject();
    std::unique_ptr<Models::AccessPoint> createAccessPointObject();

    Core::Status connect(std::string network, std::string password);
    Core::Status disconnect();
    void startSoftAP();
    void stopSoftAP();

    // Message handling
    std::unique_ptr<Core::IEntity> onGetConnection();
    std::unique_ptr<Core::IEntity> onCreateConnection(const Models::Connection& connection);
    std::unique_ptr<Core::IEntity> onDeleteConnection();
    std::unique_ptr<Core::IEntity> onGetAccessPoint();

    // Events handling
    void onConnected();
    void onDisconnected();
    void onClientConnected();
    void onClientDisconnected();

    // Access point automatic shutdown
    static void onDisconnectStatic(WiFiManager* manager);
    void startDisconnectTimer();
    void stopDisconnectTimer();
    void onDisconnectTimeout();
};

}

#endif /* end of include guard: SERVICES_WIFIMANAGER_HPP */
