// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SERIALIZATION_CONTEXT_FACTORY_HPP
#define JSON_SERIALIZATION_CONTEXT_FACTORY_HPP

#include "ISerializationContextFactory.hpp"

#include <memory>

namespace Json {

class SerializationContextFactory : public ISerializationContextFactory {
  TYPE_PTRS(SerializationContextFactory)
  public:
    // From ISerializationContextFactory
    virtual Core::StatusResult::Unique create(
      const ISerializationService& serializationService,
      ISerializationContext::Unique& context) const override;

    virtual Core::StatusResult::Unique create(
      const ISerializationService& serializationService, const String& json,
      ISerializationContext::Unique& context) const override;
};

}

#endif /* end of include guard: JSON_I_SERIALIZATION_CONTEXT_FACTORY_HPP */
