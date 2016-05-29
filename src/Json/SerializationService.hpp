// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SERIALIZATION_SERVICE_H
#define JSON_SERIALIZATION_SERVICE_H

#include "ISerializationService.hpp"

namespace Json {

class SerializationService : public ISerializationService {
  public:
    void serialize(const Core::IEntity& object,
                   const ISerializationContext& context) const override;
};

}

#endif /* end of include guard: SERVICES_SERIALIZATION_SERVICE_H */
