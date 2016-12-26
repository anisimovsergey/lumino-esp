// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef MODELS_ACCESS_POINT_HPP
#define MODELS_ACCESS_POINT_HPP

#include "WString.h"
#include "Core/IEntity.hpp"

namespace Models {

class AccessPoint : public Core::IEntity {
  TYPE_INFO(AccessPoint, Core::IEntity, "accessPoint")
  public:
    AccessPoint(
      std::string   networkSsid
    );

    std::string  getNetworkSsid() const { return networkSsid; };

  private:
    std::string  networkSsid;
};

}

#endif /* end of include guard: MODELS_ACCESS_POINT_HPP */
