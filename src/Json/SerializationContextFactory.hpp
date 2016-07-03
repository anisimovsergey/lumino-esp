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
  public:
    // From ISerializationContextFactory
    virtual std::unique_ptr<Core::StatusResult> create(
      const ISerializationService& serializationService,
      std::unique_ptr<ISerializationContext>& context) const override;

    virtual std::unique_ptr<Core::StatusResult> create(
      const ISerializationService& serializationService, const String& json,
      std::unique_ptr<ISerializationContext>& context) const override;
};

}

#endif /* end of include guard: JSON_I_SERIALIZATION_CONTEXT_FACTORY_HPP */
