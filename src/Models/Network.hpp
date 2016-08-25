// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef MODELS_NETWORK_HPP
#define MODELS_NETWORK_HPP

#include "WString.h"
#include "Core/IEntity.hpp"

namespace Models {

class Network : public Core::IEntity {
  TYPE_INFO(Network, Core::IEntity, "network")
  public:
    Network(std::string ssid, int rssi, int encryptionType);

    std::string  getSsid() const { return ssid; };
    int     getRssi() const { return rssi; };
    int     getEncryptionType() const { return encryptionType; };

  private:
    std::string  ssid;
    int     rssi;
    int     encryptionType;
};

}

#endif /* end of include guard: MODELS_NETWORK_HPP */
