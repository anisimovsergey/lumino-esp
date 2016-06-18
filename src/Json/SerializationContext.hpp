// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SERIALIZATION_CONTEXT_H
#define JSON_SERIALIZATION_CONTEXT_H

#include "ISerializationContext.hpp"
#include "ISerializationService.hpp"

#include <ArduinoJson.h>

#include <memory>

namespace Json {

class SerializationContext : public ISerializationContext {
  public:

    static std::shared_ptr<Core::ActionResult> create(
      const ISerializationService& serializationService,
      std::shared_ptr<ISerializationContext>& context);

    static std::shared_ptr<Core::ActionResult> create(
      const ISerializationService& serializationService,
      std::shared_ptr<ISerializationContext>& context,
      const String& json);

    String toString() const override;

    std::shared_ptr<Core::ActionResult>
      getStringValue(const String& key, String& value) override;
    std::shared_ptr<Core::ActionResult>
      getBoolValue(const String& key, bool& value) override;

    void setValue(const String& key, const String& value) override;
    void setValue(const String& key, int value) override;
    void setValue(const String& key, bool value) override;
    void setValue(const String& key, const Core::IList& list) override;

  private:
    const ISerializationService&  serializationService;
    std::shared_ptr<DynamicJsonBuffer>      jsonBuffer;
    JsonObject&                             jsonObject;

    SerializationContext(
      const ISerializationService& serializationService,
      std::shared_ptr<DynamicJsonBuffer> jsonBuffer,
      JsonObject& jsonObject);
};

}

#endif /* end of include guard: JSON_SERIALIZATION_CONTEXT_H */
