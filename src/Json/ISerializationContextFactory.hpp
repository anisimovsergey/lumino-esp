// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_I_SERIALIZATION_CONTEXT_FACTORY_HPP
#define JSON_I_SERIALIZATION_CONTEXT_FACTORY_HPP

#include "ISerializationContext.hpp"
#include "ISerializationService.hpp"

#include <memory>

namespace Json {

class ISerializationContextFactory {
  public:
    virtual ~ISerializationContextFactory() {}

    virtual std::unique_ptr<Core::StatusResult> create(
      const ISerializationService& serializationService,
      std::unique_ptr<ISerializationContext>& context) const = 0;

    virtual std::unique_ptr<Core::StatusResult> create(
      const ISerializationService& serializationService, const String& json,
      std::unique_ptr<ISerializationContext>& context) const = 0;
};

}

#endif /* end of include guard: JSON_I_SERIALIZATION_CONTEXT_FACTORY_HPP */