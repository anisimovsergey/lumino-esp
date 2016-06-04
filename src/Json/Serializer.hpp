// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include "ISerializer.hpp"

namespace Json {

template <class T> class Serializer : public ISerializer {
  public:
    void serialize(
      const Core::IEntity& entity,
      ISerializationContext& context) const override {

      const T& entityT = static_cast<const T&>(entity);
      serialize(entityT, context);
    }

    virtual Core::Status deserialize(
      std::shared_ptr<Core::IEntity>& entity,
      ISerializationContext& context) const override {

      std::shared_ptr<T> entityT;
      Core::Status status = deserialize(entityT, context);
      entity = entityT;
      return status;
    }

  protected:
    virtual void serialize(
      const T& entity,
      ISerializationContext& context) const = 0;

    virtual Core::Status deserialize(
      std::shared_ptr<T>& entity,
      ISerializationContext& context) const {

      return Core::Status::NotSupported;
    }
 };

}

#endif /* end of include guard: JSON_SERIALIZER_H */
