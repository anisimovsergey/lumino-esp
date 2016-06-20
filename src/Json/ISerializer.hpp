// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_I_SERIALIZER_HPP
#define JSON_I_SERIALIZER_HPP

#include "Core/IEntity.hpp"
#include "ISerializationContext.hpp"

#include "memory"

namespace Json {

class ISerializer {
  public:
    virtual ~ISerializer() {};

    virtual std::shared_ptr<Core::IActionResult> serialize(
      const Core::IEntity& entity,
      ISerializationContext& context) const = 0;

    virtual std::shared_ptr<Core::IActionResult> deserialize(
      std::shared_ptr<Core::IEntity>& entity,
      ISerializationContext& context) const = 0;

    virtual String getTypeId() const = 0;
};

}

#endif /* end of include guard: JSON_I_SERIALIZER_HPP */
