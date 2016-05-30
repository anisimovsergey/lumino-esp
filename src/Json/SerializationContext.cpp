#include "SerializationContext.hpp"

using namespace Json;
using namespace Core;

SerializationContext::SerializationContext(
  const ISerializationService& serializationService,
  std::shared_ptr<DynamicJsonBuffer> jsonBuffer,
  JsonObject& jsonObject) :
  serializationService(serializationService),
  jsonBuffer(jsonBuffer),
  jsonObject(jsonObject) {
}

std::shared_ptr<ISerializationContext>
SerializationContext::create(
  const ISerializationService& serializationService) {

  std::shared_ptr<DynamicJsonBuffer> jsonBuffer(new DynamicJsonBuffer);
  JsonObject& jsonObject = jsonBuffer->createObject();

  auto context = new SerializationContext(
    serializationService,
    jsonBuffer,
    jsonObject);

  return std::shared_ptr<ISerializationContext>(context);
}

String
SerializationContext::toString() const {
  String str;
  jsonObject.printTo(str);
  return str;
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
  list.forEach([&](const IEntity& element) {
    JsonObject& nestedObject = array.createNestedObject();
    SerializationContext context(serializationService, jsonBuffer, nestedObject);
    serializationService.serialize(element, context);
  });
}
