// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SERIALIZER_HPP
#define JSON_SERIALIZER_HPP

#include "ISerializer.hpp"

namespace Json {

template <class T> class Serializer : public ISerializer {
  public:
    virtual std::shared_ptr<Core::IActionResult> serialize(
      const Core::IEntity& entity,
      ISerializationContext& context) const override {

      const T& entityT = static_cast<const T&>(entity);
      return serialize(entityT, context);
    }

    virtual std::shared_ptr<Core::IActionResult> deserialize(
      std::shared_ptr<Core::IEntity>& entity,
      ISerializationContext& context) const override {

      std::shared_ptr<T> entityT;
      auto actionResult = deserialize(entityT, context);
      entity = entityT;
      return actionResult;
    }

  protected:
    virtual std::shared_ptr<Core::IActionResult> serialize(
      const T& entity,
      ISerializationContext& context) const = 0;

    virtual std::shared_ptr<Core::IActionResult> deserialize(
      std::shared_ptr<T>& entity,
      ISerializationContext& context) const = 0;
 };

}

#endif /* end of include guard: JSON_SERIALIZER_HPP */
