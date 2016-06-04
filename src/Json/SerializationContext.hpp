// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SERIALIZATION_CONTEXT_H
#define JSON_SERIALIZATION_CONTEXT_H

#include "ISerializationContext.hpp"
#include "ISerializationService.hpp"
#include "Core/Status.hpp"

#include <ArduinoJson.h>

#include <memory>

namespace Json {

class SerializationContext : public ISerializationContext {
  public:
    static std::shared_ptr<ISerializationContext> create(
      const ISerializationService& serializationService);
    static Core::Status create(
      const ISerializationService& serializationService,
      const String& json,
      std::shared_ptr<ISerializationContext>& context);

    String toString() const override;

    Core::Status getStringValue(const String& key, String& value) override;
    Core::Status getBoolValue(const String& key, bool& value) override;

    void setValue(const String& key, const String& value) override;
    void setValue(const String& key, int value) override;
    void setValue(const String& key, const Core::IList& list) override;

  private:
    SerializationContext(
      const ISerializationService& serializationService,
      std::shared_ptr<DynamicJsonBuffer> jsonBuffer,
      JsonObject& jsonObject);

    const ISerializationService&  serializationService;
    std::shared_ptr<DynamicJsonBuffer>      jsonBuffer;
    JsonObject&                             jsonObject;
};

}

#endif /* end of include guard: JSON_SERIALIZATION_CONTEXT_H */
