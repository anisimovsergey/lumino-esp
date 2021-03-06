// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Lumino
// https://github.com/anisimovsergey/lumino-esp

#ifndef MODELS_CONNECTION_HPP
#define MODELS_CONNECTION_HPP

#include "Core/IEntity.hpp"

namespace Models {

class Connection final : public Core::IEntity {
  TYPE_INFO(Connection, Core::IEntity, "connection")
  public:
    Connection(
      std::string ssid,
      bool        isConnected,
      bool        isProtected,
      int         rssi,
      uint32_t    localIP,
      uint32_t    subnetMask,
      uint32_t    gatewayIP,
      uint32_t    dnsIP,
      int         disconnectReason
    );

    Connection(
      std::string  ssid,
      std::string  password
    );

    std::string  getSsid() const { return ssid; };
    std::string  getPassword() const { return password; };
    bool         getIsConnected() const { return isConnected; };
    bool         getIsProtected() const { return isProtected; };
    int          getRssi() const { return rssi; };
    uint32_t     getLocalIP() const { return localIP; };
    uint32_t     getSubnetMask() const { return subnetMask; };
    uint32_t     getGatewayIP() const { return gatewayIP; };
    uint32_t     getDnsIP() const { return dnsIP; };
    int          getDisconnectReason() const { return disconnectReason; };

  private:
    std::string  ssid;
    std::string  password;
    bool         isConnected;
    bool         isProtected;
    int          rssi;
    uint32_t     localIP;
    uint32_t     subnetMask;
    uint32_t     gatewayIP;
    uint32_t     dnsIP;
    int          disconnectReason;
};

}

#endif /* end of include guard: MODELS_CONNECTION_HPP */
