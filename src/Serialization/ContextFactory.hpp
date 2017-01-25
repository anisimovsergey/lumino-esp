// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERIALIZATION_CONTEXT_FACTORY_HPP
#define SERIALIZATION_CONTEXT_FACTORY_HPP

#include "Serialization/IContextFactory.hpp"

#include <memory>

namespace Serialization {

class ContextFactory : public IContextFactory {
  TYPE_PTRS(ContextFactory)
  public:
    // From ISerializationContextFactory
    virtual Core::Status createSerializationContext(
      const ISerializationService& serializationService,
      ISerializationContext::Unique& context) const override;

    virtual Core::Status createDeserializationContext(
      const ISerializationService& serializationService, const std::string& json,
      IDeserializationContext::Unique& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_CONTEXT_FACTORY_HPP */
