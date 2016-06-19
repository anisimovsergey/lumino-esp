// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SERIALIZATION_CONTEXT_FACTORY_H
#define JSON_SERIALIZATION_CONTEXT_FACTORY_H

#include "ISerializationContextFactory.hpp"

#include <memory>

namespace Json {

class SerializationContextFactory : public ISerializationContextFactory {
  public:
    std::shared_ptr<Core::IActionResult> create(
      const ISerializationService& serializationService,
      std::shared_ptr<ISerializationContext>& context) const override;

    std::shared_ptr<Core::IActionResult> create(
      const ISerializationService& serializationService,
      std::shared_ptr<ISerializationContext>& context,
      const String& json) const override;
};

}

#endif /* end of include guard: JSON_I_SERIALIZATION_CONTEXT_FACTORY_H */
