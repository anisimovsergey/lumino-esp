// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERIALIZATION_DESERIALIZATION_CONTEXT_HPP
#define SERIALIZATION_DESERIALIZATION_CONTEXT_HPP

#include "Serialization/IDeserializationContext.hpp"

#include <ArduinoJson.h>

#include <memory>

namespace Serialization {

struct ISerializationService;

class DeserializationContext : public IDeserializationContext {
  public:
    DeserializationContext(
      const ISerializationService& serializationService,
      std::shared_ptr<const DynamicJsonBuffer> jsonBuffer,
      JsonObject& jsonObject);

    // From IDeserializationContext
    virtual bool hasKey(const std::string& key) override;

    virtual Core::Status
      getString(const std::string& key, std::string& value) override;
    virtual Core::Status
      getInt(const std::string& key, int& value) override;
    virtual Core::Status
      getBool(const std::string& key, bool& value) override;
    virtual Core::Status
      getEntity(const std::string& key, std::unique_ptr<Core::IEntity>& entity) override;

  private:
    const ISerializationService&              serializationService;
    std::shared_ptr<const DynamicJsonBuffer>  jsonBuffer;
    JsonObject&                               jsonObject;
};

}

#endif /* end of include guard: SERIALIZATION_SERIALIZATION_CONTEXT_HPP */
