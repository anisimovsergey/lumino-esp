// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_REQUEST_SERIALIZER_HPP
#define JSON_REQUEST_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Core/IMessage.hpp"

namespace Json {

class RequestSerializer : public Serializer<Core::Request> {
  public:
    // From ISerializer
    virtual String getTypeId() const override {
      return Core::Request::TypeId;
    }

  protected:
    // From Serializer
    virtual std::unique_ptr<Core::StatusResult> serialize(
      const Core::Request& request,
      ISerializationContext& context) const override;

    virtual std::unique_ptr<Core::StatusResult> deserialize(
      std::unique_ptr<Core::Request>& request,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_SETTINGS_SERIALIZER_HPP */
