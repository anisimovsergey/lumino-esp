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
    virtual std::tuple<Core::Status, std::unique_ptr<ISerializationContext>> createSerializationContext(
      const ISerializationService& serializationService) const override;

    virtual std::tuple<Core::Status, std::unique_ptr<IDeserializationContext>> createDeserializationContext(
      const ISerializationService& serializationService, const std::string& json) const override;
};

}

#endif /* end of include guard: SERIALIZATION_CONTEXT_FACTORY_HPP */
