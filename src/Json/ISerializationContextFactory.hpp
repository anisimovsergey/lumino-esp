// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_I_SERIALIZATION_CONTEXT_FACTORY_H
#define JSON_I_SERIALIZATION_CONTEXT_FACTORY_H

#include "ISerializationContext.hpp"
#include "ISerializationService.hpp"

#include <memory>

namespace Json {

class ISerializationContextFactory {
  public:
    virtual ~ISerializationContextFactory() {}

    virtual std::shared_ptr<ISerializationContext> create(
      const ISerializationService& serializationService) const = 0;
};

}

#endif /* end of include guard: JSON_I_SERIALIZATION_CONTEXT_FACTORY_H */
