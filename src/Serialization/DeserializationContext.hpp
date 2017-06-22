// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Lumino
// https://github.com/anisimovsergey/lumino-esp

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
    virtual bool hasKey(const std::string& key) const override;

    virtual std::tuple<Core::Status, std::string>
      getString(const std::string& key) const override;
    virtual std::tuple<Core::Status, int>
      getInt(const std::string& key) const override;
    virtual std::tuple<Core::Status, float>
      getFloat(const std::string& key) const override;
    virtual std::tuple<Core::Status, bool>
      getBool(const std::string& key) const override;
    virtual std::tuple<Core::Status, std::unique_ptr<Core::IEntity>>
      getEntity(const std::string& key) const override;

  private:
    const ISerializationService&              serializationService;
    std::shared_ptr<const DynamicJsonBuffer>  jsonBuffer;
    JsonObject&                               jsonObject;
};

}

#endif /* end of include guard: SERIALIZATION_SERIALIZATION_CONTEXT_HPP */
