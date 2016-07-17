// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_I_SERIALIZATION_SERVICE_HPP
#define JSON_I_SERIALIZATION_SERVICE_HPP

#include "ISerializationContext.hpp"

#include "Core/IEntity.hpp"

#include <memory>

namespace Json {

class ISerializationService {
  public:
    virtual ~ISerializationService();

    virtual std::unique_ptr<Core::StatusResult> serialize(
      const Core::IEntity& object,
      String& json) const = 0;

    virtual std::unique_ptr<Core::StatusResult> serialize(
      const Core::IEntity& object,
      ISerializationContext& context) const = 0;

    virtual std::unique_ptr<Core::StatusResult> deserialize(
      const String& json,
      std::unique_ptr<Core::IEntity>& entity) const = 0;

    virtual std::unique_ptr<Core::StatusResult> deserialize(
      ISerializationContext& context,
      std::unique_ptr<Core::IEntity>& entity) const = 0;
};

}

#endif /* end of include guard: SERVICES_I_SERIALIZATION_SERVICE_HPP */
