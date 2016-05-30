// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_I_SERIALIZATION_SERVICE_H
#define JSON_I_SERIALIZATION_SERVICE_H

#include "ISerializationContext.hpp"

namespace Json {

class ISerializationService {
  public:
    virtual ~ISerializationService() {}

    virtual String serialize(const Core::IEntity& object) const = 0;
    virtual void serialize(const Core::IEntity& object,
                           ISerializationContext& context) const = 0;
};

}

#endif /* end of include guard: SERVICES_I_SERIALIZATION_SERVICE_H */
