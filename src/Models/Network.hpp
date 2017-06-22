// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Lumino
// https://github.com/anisimovsergey/lumino-esp

#ifndef MODELS_NETWORK_HPP
#define MODELS_NETWORK_HPP

#include "Core/IEntity.hpp"

namespace Models {

class Network final : public Core::IEntity {
  TYPE_INFO(Network, Core::IEntity, "network")
  public:
    Network(std::string ssid, int rssi, std::string encryptionType);

    std::string  getSsid() const { return ssid; };
    int          getRssi() const { return rssi; };
    std::string  getEncryption() const { return encryption; };

  private:
    std::string   ssid;
    int           rssi;
    std::string   encryption;
};

}

#endif /* end of include guard: MODELS_NETWORK_HPP */
