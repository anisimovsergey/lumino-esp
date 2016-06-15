// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef MODELS_NETWORKS_SCAN_H
#define MODELS_NETWORKS_SCAN_H

#include "Network.hpp"

#include "Core/Entity.hpp"
#include "Core/List.hpp"

#include <memory>

namespace Models {

class NetworksScan : public Core::Entity<NetworksScan> {
  public:
    NetworksScan(String status, Core::List<Network> networks);

    static String  getStaticTypeId() { return "networks_scan"; }

    String  getStatus() const { return status; };
    Core::List<Network> getNetworks() const { return networks; };

  private:
    String  status;
    Core::List<Network> networks;
};

}

#endif /* end of include guard: MODELS_NETWORKS_SCAN_H */
