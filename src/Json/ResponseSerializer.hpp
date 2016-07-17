// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_RESPONSE_SERIALIZER_HPP
#define JSON_RESPONSE_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Core/IMessage.hpp"

namespace Json {

class ResponseSerializer : public Serializer<Core::Response> {
  public:
    // From ISerializer
    virtual String getTypeId() const override {
      return Core::Response::TypeId;
    }

  protected:
    // From Serializer
    virtual std::unique_ptr<Core::StatusResult> serialize(
      const Core::Response& response,
      ISerializationContext& context) const override;

    virtual std::unique_ptr<Core::StatusResult> deserialize(
      std::unique_ptr<Core::Response>& response,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_SETTINGS_SERIALIZER_HPP */
