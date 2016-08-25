// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef MODELS_CONNECTION_HPP
#define MODELS_CONNECTION_HPP

#include "WString.h"
#include "Core/IEntity.hpp"

namespace Models {

class Connection : public Core::IEntity {
  TYPE_INFO(Connection, Core::IEntity, "connection")
  public:
    Connection(
      std::string  networkSsid,
      bool    isConnected
    );

    Connection(
      std::string  networkSsid,
      std::string  networkPassword
    );

    std::string  getNetworkSsid() const { return networkSsid; };
    std::string  getNetworkPassword() const { return networkPassword; };
    bool    getIsConnected() const { return isConnected; };

  private:
    std::string  networkSsid;
    std::string  networkPassword;
    bool    isConnected;
};

}

#endif /* end of include guard: MODELS_CONNECTION_HPP */
