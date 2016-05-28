// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_STATUS_CODE_REGISTRY_H
#define SERVICES_STATUS_CODE_REGISTRY_H

#include "IStatusCodeRegistry.hpp"

namespace Services {

class StatusCodeRegistry : public IStatusCodeRegistry  {
  public:
    int getCode(const Core::Status& status) const override;
};

}

#endif /* end of include guard: CORE_I_STATUS_CODE_REGISTRY_H */
