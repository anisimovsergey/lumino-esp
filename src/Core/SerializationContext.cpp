#include "SerializationContext.hpp"

using namespace Core;

SerializationContext::SerializationContext(
  const ISerializationService& serializationService,
  JsonObject& jsonObject) :
  serializationService(serializationService),
  jsonObject(jsonObject) {
}

void
SerializationContext::setValue(const String& key, const String& value) {
  jsonObject[key] = value;
}

void
SerializationContext::setValue(const String& key, int value) {
  jsonObject[key] = value;
}

void
SerializationContext::setValue(const String& key, const IList& list) {
  JsonArray& array = jsonObject.createNestedArray(key);
  list.forEach([&](const ISerializable& element) {
    JsonObject& nestedObject = array.createNestedObject();
    SerializationContext context(serializationService, nestedObject);
    serializationService.serialize(context, element);
  });
}
