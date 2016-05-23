// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include "IWiFiManager.hpp"

class WiFiManager : public IWiFiManager {
  public:
    virtual bool isConnected() override;
    virtual void connect() override;
    virtual void disconnect() override;
};

#endif /* end of include guard: HTTPSERVER_H */
