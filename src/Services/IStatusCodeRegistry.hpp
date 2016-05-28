// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_I_STATUS_CODE_REGISTRY_H
#define SERVICES_I_STATUS_CODE_REGISTRY_H

#include "Core/Status.hpp"

namespace Services {

class IStatusCodeRegistry {
  public:
    virtual int getCode(const Core::Status& status) const = 0;
};

}

#endif /* end of include guard: CORE_I_STATUS_CODE_REGISTRY_H */
