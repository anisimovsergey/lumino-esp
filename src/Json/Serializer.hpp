// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SERIALIZER_HPP
#define JSON_SERIALIZER_HPP

#include "ISerializer.hpp"

#include "Core/StatusResult.hpp"

namespace Json {

template <class T> class Serializer : public ISerializer {
  public:
    // From ISerializer
    virtual String getTypeId() const override {
      return T::TypeId;
    }

    virtual Core::StatusResult::Unique serialize(
      const Core::IEntity& entity,
      ISerializationContext& context) const override {

      auto& entityT = static_cast<const T&>(entity);
      auto result = serialize(entityT, context);
      if (!result->isOk()) {
        return Core::StatusResult::makeUnique(Core::StatusCode::InternalServerError,
          "Unable to serialize an instance of type """ + getTypeId() + """.",
          std::move(result));
      }
      return result;
    }

    virtual std::unique_ptr<Core::StatusResult> deserialize(
      std::unique_ptr<Core::IEntity>& entity,
      ISerializationContext& context) const override {
      std::unique_ptr<T> entityT;
      auto result = deserialize(entityT, context);
      if (!result->isOk()) {
        return Core::StatusResult::makeUnique(Core::StatusCode::InternalServerError,
          "Unable to deserialize an instance of type """ + getTypeId() + """.",
          std::move(result));
      }
      entity = std::move(entityT);
      return result;
    }

  protected:
    virtual std::unique_ptr<Core::StatusResult> serialize(
      const T& entity,
      ISerializationContext& context) const = 0;

    virtual std::unique_ptr<Core::StatusResult> deserialize(
      std::unique_ptr<T>& entity,
      ISerializationContext& context) const = 0;
 };

}

#endif /* end of include guard: JSON_SERIALIZER_HPP */
