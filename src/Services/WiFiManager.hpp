// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_WIFIMANAGER_H
#define SERVICES_WIFIMANAGER_H

#include "IWiFiManager.hpp"

namespace Services {

class WiFiManager : public IWiFiManager {
  public:
    Core::Status getWiFiNetworks(Networks& networks) const override;

    String getDeviceName() override;
    String getNetwork() override;
    String getPassword() override;
    bool isConnected() const override;

    void connect(String network, String password) override;
    void disconnect() override;
};

}

#endif /* end of include guard: SERVICES_WIFIMANAGER_H */
