// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_SERIALIZATION_CONTEXT_H
#define CORE_SERIALIZATION_CONTEXT_H

#include "ISerializationContext.hpp"

#include <ArduinoJson.h>

namespace Core {

class ISerializationService {
  public:
    virtual ~ISerializationService() {}

    virtual void serialize(const ISerializationContext& context,
                           const ISerializable& object) const = 0;
};

class SerializationContext : public ISerializationContext {
  public:
    SerializationContext(const ISerializationService& serializationService,
                         JsonObject& jsonObject);

    void setValue(const String& key, const String& value) override;
    void setValue(const String& key, int value) override;
    void setValue(const String& key, const IList& list) override;

  private:
    JsonObject&                   jsonObject;
    const ISerializationService&  serializationService;
};

}

#endif /* end of include guard: CORE_SERIALIZATION_CONTEXT_H */
