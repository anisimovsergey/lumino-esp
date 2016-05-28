// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_WIFISERVICE_H
#define SERVICES_I_WIFISERVICE_H

#include "Core/Status.hpp"
#include "Core/List.hpp"
#include "Models/Network.hpp"

namespace Services {

class IWiFiService {
  public:
    typedef Core::List<Models::Network> Networks;

    virtual Core::Status getWiFiNetworks(Networks& networks) const = 0;
};

}

#endif /* end of include guard: SERVICES_I_WIFISERVICE_H */
