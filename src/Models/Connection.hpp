// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef MODELS_CONNECTION_HPP
#define MODELS_CONNECTION_HPP

#include "Core/Entity.hpp"

namespace Models {

class Connection : public Core::Entity<Connection> {
  public:
    Connection(
      String  networkSsid,
      bool    isConnected
    );

    Connection(
      String  networkSsid,
      String  networkPassword
    );

    static String  getStaticTypeId() { return "connection"; }

    String  getNetworkSsid() const { return networkSsid; };
    String  getNetworkPassword() const { return networkPassword; };
    bool    getIsConnected() const { return isConnected; };

  private:
    String  networkSsid;
    String  networkPassword;
    bool    isConnected;
};

}

#endif /* end of include guard: MODELS_CONNECTION_HPP */
