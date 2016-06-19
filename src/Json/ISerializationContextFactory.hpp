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

    virtual std::shared_ptr<Core::IActionResult> create(
      const ISerializationService& serializationService,
      std::shared_ptr<ISerializationContext>& context) const = 0;

    virtual std::shared_ptr<Core::IActionResult> create(
      const ISerializationService& serializationService,
      std::shared_ptr<ISerializationContext>& context,
      const String& json) const = 0;
};

}

#endif /* end of include guard: JSON_I_SERIALIZATION_CONTEXT_FACTORY_H */
