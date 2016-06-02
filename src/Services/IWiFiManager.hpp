// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_WIFIMANAGER_H
#define SERVICES_I_WIFIMANAGER_H

#include "Core/List.hpp"
#include "Core/Status.hpp"
#include "Models/Network.hpp"

namespace Services {

class IWiFiManager {
  public:
    virtual ~IWiFiManager() {};

    typedef Core::List<Models::Network> Networks;
    virtual Core::Status getWiFiNetworks(Networks& networks) const = 0;

    virtual String getDeviceName() = 0;
    virtual String getNetwork() = 0;
    virtual String getPassword() = 0;
    virtual bool isConnected() const = 0;

    virtual void connect(String network, String password) = 0;
    virtual void disconnect() = 0;
};

}

#endif /* end of include guard: SERVICES_I_WIFIMANAGER_H */
