// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SERIALIZATION_CONTEXT_HPP
#define JSON_SERIALIZATION_CONTEXT_HPP

#include "ISerializationContext.hpp"
#include "ISerializationService.hpp"

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
    String toString() const override;

    virtual bool hasKey(const String& key) override;

    virtual std::unique_ptr<Core::StatusResult>
      getStringValue(const String& key, String& value) override;
    virtual std::unique_ptr<Core::StatusResult>
      getBoolValue(const String& key, bool& value) override;
    virtual std::unique_ptr<Core::StatusResult>
      getEntity(const String& key, std::unique_ptr<Core::IEntity>& entity) override;

    virtual std::unique_ptr<Core::StatusResult>
      setValue(const String& key, const String& value) override;
    virtual std::unique_ptr<Core::StatusResult>
      setValue(const String& key, int value) override;
    virtual std::unique_ptr<Core::StatusResult>
      setValue(const String& key, bool value) override;
    virtual std::unique_ptr<Core::StatusResult>
      setValue(const String& key, const Core::IList& list) override;
    virtual std::unique_ptr<Core::StatusResult>
      setValue(const String& key, const Core::IEntity& entity) override;

  private:
    const ISerializationService&              serializationService;
    std::shared_ptr<const DynamicJsonBuffer>  jsonBuffer;
    JsonObject&                               jsonObject;
};

}

#endif /* end of include guard: JSON_SERIALIZATION_CONTEXT_HPP */
