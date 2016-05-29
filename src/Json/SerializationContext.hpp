// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_SERIALIZATION_CONTEXT_H
#define CORE_SERIALIZATION_CONTEXT_H

#include "ISerializationContext.hpp"
#include "ISerializationService.hpp"

#include <ArduinoJson.h>

namespace Json {

class SerializationContext : public ISerializationContext {
  public:
    SerializationContext(
      const ISerializationService& serializationService,
      JsonObject& jsonObject);

    void setValue(const String& key, const String& value) override;
    void setValue(const String& key, int value) override;
    void setValue(const String& key, const Core::IList& list) override;

  private:
    JsonObject&                             jsonObject;
    const ISerializationService&  serializationService;
};

}

#endif /* end of include guard: CORE_SERIALIZATION_CONTEXT_H */
