// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Lumino
// https://github.com/anisimovsergey/lumino-esp

#ifndef MODELS_ACCESS_POINT_HPP
#define MODELS_ACCESS_POINT_HPP

#include "Core/IEntity.hpp"

namespace Models {

class AccessPoint final : public Core::IEntity {
  TYPE_INFO(AccessPoint, Core::IEntity, "accessPoint")
  public:
    AccessPoint(std::string networkSsid);

    std::string getNetworkSsid() const { return networkSsid; };

  private:
    std::string networkSsid;
};

}

#endif /* end of include guard: MODELS_ACCESS_POINT_HPP */
