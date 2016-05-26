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
    virtual bool isConnected() override;
    virtual void connect() override;
    virtual void disconnect() override;
};

}

#endif /* end of include guard: SERVICES_WIFIMANAGER_H */
