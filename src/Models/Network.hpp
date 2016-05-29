// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef MODELS_NETWORK_H
#define MODELS_NETWORK_H

#include "Core/IEntity.hpp"

namespace Models {

class Network : public Core::IEntity {
  public:
    Network(String ssid, int rssi, int encryptionType);

    String getTypeId() const override { return "network"; }

    String  getSsid() const { return ssid; };
    int     getRssi() const { return rssi; };
    int     getEncryptionType() const { return encryptionType; };

  private:
    String  ssid;
    int     rssi;
    int     encryptionType;
};

}

#endif /* end of include guard: MODELS_NETWORK_H */
