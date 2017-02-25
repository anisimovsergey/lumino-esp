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
  public:
    // From IContextFactory
    virtual Core::Status createSerializationContext(
      const ISerializationService& serializationService,
      std::unique_ptr<ISerializationContext>& context) const override;

    virtual Core::Status createDeserializationContext(
      const ISerializationService& serializationService, const std::string& json,
      std::unique_ptr<IDeserializationContext>& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_CONTEXT_FACTORY_HPP */
