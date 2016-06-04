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

Status
SerializationContext::create(
  const ISerializationService& serializationService,
  const String& json,
  std::shared_ptr<ISerializationContext>& context) {

  std::shared_ptr<DynamicJsonBuffer> jsonBuffer(new DynamicJsonBuffer);
  JsonObject& jsonObject = jsonBuffer->parseObject(json);
  if (!jsonObject.success())
    return Status::UnableToParseJson;

  context = std::shared_ptr<SerializationContext>(new SerializationContext(
    serializationService,
    jsonBuffer,
    jsonObject));

  return Status::Ok;
}

String
SerializationContext::toString() const {
  String str;
  jsonObject.printTo(str);
  return str;
}

Status
SerializationContext::getStringValue(const String& key, String& value) {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return Status::UnableToFindJsonKey(key);

  if (!jsonVal.is<const char*>())
    return Status::ValueIsNotString;

  value = (const char*)jsonVal;
  return Status::Ok;
}

Status
SerializationContext::getBoolValue(const String& key, bool& value) {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return Status::UnableToFindJsonKey(key);

  if (!jsonVal.is<bool>())
    return Status::ValueIsNotBool;

  value = (bool)jsonVal;
  return Status::Ok;
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
SerializationContext::setValue(const String& key, bool value) {
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
