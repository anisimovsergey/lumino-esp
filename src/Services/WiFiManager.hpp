// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_WIFIMANAGER_HPP
#define SERVICES_WIFIMANAGER_HPP

#include "IWiFiManager.hpp"
#include "Core/ILoopedService.hpp"
#include "Core/IMessageQueue.hpp"

#include <DNSServer.h>

#include <memory>

namespace Services {

class WiFiManager : public IWiFiManager, public Core::ILoopedService {
  public:
    WiFiManager(std::shared_ptr<Core::IMessageQueue> messageQueue);

    void    initialize();

    std::unique_ptr<Core::StatusResult> getWiFiNetworks(
      std::unique_ptr<Core::List<Models::Network>>& networks) const override;

    String  getDeviceName() const override;
    bool    hasConnection() const override;
    String  getNetwork() const override;
    bool    isConnected() const override;

    std::unique_ptr<Core::StatusResult>
      connect(String network, String password) override;
    std::unique_ptr<Core::StatusResult>
      disconnect() override;

    void loop() override;

  private:
    std::unique_ptr<DNSServer> dnsServer;
    std::shared_ptr<Core::IMessageQueue> messageQueue;
    String  deviceName;
    bool    delayed_disconnect;

    void    startSoftAP();
    void    stopSoftAP();
};

}

#endif /* end of include guard: SERVICES_WIFIMANAGER_HPP */
