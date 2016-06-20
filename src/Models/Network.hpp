// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef MODELS_NETWORK_HPP
#define MODELS_NETWORK_HPP

#include "Core/Entity.hpp"

namespace Models {

class Network : public Core::Entity<Network> {
  public:
    Network(String ssid, int rssi, int encryptionType);

    static String  getStaticTypeId() { return "network"; }

    String  getSsid() const { return ssid; };
    int     getRssi() const { return rssi; };
    int     getEncryptionType() const { return encryptionType; };

  private:
    String  ssid;
    int     rssi;
    int     encryptionType;
};

}

#endif /* end of include guard: MODELS_NETWORK_HPP */
