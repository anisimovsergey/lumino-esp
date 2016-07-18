// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_OBJECT_RESULT_SERIALIZER_HPP
#define JSON_OBJECT_RESULT_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Core/IMessage.hpp"

namespace Json {

class ObjectResultSerializer : public Serializer<Core::ObjectResult> {
  public:
    // From ISerializer
    // TODO: Remove these methods from all the serializers
    virtual String getTypeId() const override {
      return Core::ObjectResult::TypeId;
    }

  protected:
    // From Serializer
    virtual std::unique_ptr<Core::StatusResult> serialize(
      const Core::ObjectResult& objectResult,
      ISerializationContext& context) const override;

    virtual std::unique_ptr<Core::StatusResult> deserialize(
      std::unique_ptr<Core::ObjectResult>& objectResult,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_OBJECT_RESULT_SERIALIZER_HPP */
