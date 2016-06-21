// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_WIFIMANAGER_HPP
#define SERVICES_WIFIMANAGER_HPP

#include "IWiFiManager.hpp"
#include "ILoopedService.hpp"

#include <DNSServer.h>

#include <memory>

namespace Services {

class WiFiManager : public IWiFiManager, public ILoopedService {
  public:
    WiFiManager();

    void    initialize();

    std::unique_ptr<Core::IActionResult>
      getWiFiNetworks(std::shared_ptr<Core::List<Models::Network>>& networks) const override;

    String  getDeviceName() const override;
    bool    hasConnection() const override;
    String  getNetwork() const override;
    bool    isConnected() const override;

    std::unique_ptr<Core::IActionResult>
      connect(String network, String password) override;
    std::unique_ptr<Core::IActionResult>
      disconnect() override;

    void loop() override;

  private:
    std::unique_ptr<DNSServer> dnsServer;

    String  deviceName;
    String  network;
    String  password;
};

}

#endif /* end of include guard: SERVICES_WIFIMANAGER_HPP */
