// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef WIFISERVICE_H
#define WIFISERVICE_H

#include "IWiFiService.hpp"

class WiFiService : public IWiFiService {
  public:
    virtual bool getWiFiNetworks(std::list<Network>& networks) const override;
};

#endif /* end of include guard: HTTPSERVER_H */
