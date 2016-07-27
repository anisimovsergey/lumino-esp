// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_WIFIMANAGER_HPP
#define SERVICES_I_WIFIMANAGER_HPP

#include "Core/List.hpp"
#include "Core/ActionResult.hpp"
#include "Models/Network.hpp"

#include <memory>

namespace Services {

class IWiFiManager {
  public:
    virtual ~IWiFiManager();

    virtual String  getDeviceName() const = 0;
    virtual bool    hasConnection() const = 0;
    virtual String  getNetwork() const = 0;
    virtual bool    isConnected() const = 0;

    virtual Core::StatusResult::Unique connect(
      String network, String password) = 0;
    virtual Core::StatusResult::Unique disconnect() = 0;
};

}

#endif /* end of include guard: SERVICES_I_WIFIMANAGER_HPP */
