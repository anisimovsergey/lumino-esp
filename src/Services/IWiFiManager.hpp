// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_WIFIMANAGER_H
#define SERVICES_I_WIFIMANAGER_H

namespace Services {

class IWiFiManager {
  public:
    virtual bool isConnected() = 0;
    virtual void connect() = 0;
    virtual void disconnect() = 0;
};
  
}

#endif /* end of include guard: SERVICES_I_WIFIMANAGER_H */
