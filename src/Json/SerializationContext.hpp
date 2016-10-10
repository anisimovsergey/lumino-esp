// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SERIALIZATION_CONTEXT_HPP
#define JSON_SERIALIZATION_CONTEXT_HPP

#include "ISerializationContext.hpp"
#include "ISerializationService.hpp"

#define ARDUINOJSON_USE_ARDUINO_STRING 0
#include <ArduinoJson.h>

#include <memory>

namespace Json {

class SerializationContext : public ISerializationContext {
  TYPE_PTRS(SerializationContext)
  public:
    SerializationContext(
      const ISerializationService& serializationService,
      std::shared_ptr<const DynamicJsonBuffer> jsonBuffer,
      JsonObject& jsonObject);

    // From ISerializationContext
    std::string toString() const override;

    virtual bool hasKey(const std::string& key) override;

    virtual Core::StatusResult::Unique
      getStringValue(const std::string& key, std::string& value) override;
    virtual Core::StatusResult::Unique
      getBoolValue(const std::string& key, bool& value) override;
    virtual Core::StatusResult::Unique
      getEntity(const std::string& key, Core::IEntity::Unique& entity) override;

    virtual Core::StatusResult::Unique
      setValue(const std::string& key, const std::string& value) override;
    virtual Core::StatusResult::Unique
      setValue(const std::string& key, int value) override;
    virtual Core::StatusResult::Unique
      setValue(const std::string& key, bool value) override;
    virtual Core::StatusResult::Unique
      setValue(const std::string& key, const Core::IList& list) override;
    virtual Core::StatusResult::Unique
      setValue(const std::string& key, const Core::IEntity& entity) override;

  private:
    const ISerializationService&              serializationService;
    std::shared_ptr<const DynamicJsonBuffer>  jsonBuffer;
    JsonObject&                               jsonObject;
};

}

#endif /* end of include guard: JSON_SERIALIZATION_CONTEXT_HPP */
