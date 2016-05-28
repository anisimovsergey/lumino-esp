// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_WIFISERVICE_H
#define SERVICES_WIFISERVICE_H

#include "IWiFiService.hpp"

namespace Services {

class WiFiService : public IWiFiService {
  public:
    virtual Core::Status getWiFiNetworks(Networks& networks) const override;
};

}

#endif /* end of include guard: SERVICES_WIFISERVICE_H */
