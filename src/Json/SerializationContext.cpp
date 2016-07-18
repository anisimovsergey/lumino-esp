#include "SerializationContext.hpp"

using namespace Json;
using namespace Core;

SerializationContext::SerializationContext(
  const ISerializationService& serializationService,
  std::shared_ptr<const DynamicJsonBuffer> jsonBuffer,
  JsonObject& jsonObject) :
    serializationService(serializationService),
    jsonBuffer(jsonBuffer),
    jsonObject(jsonObject) {
}

String
SerializationContext::toString() const {
  String str;
  jsonObject.printTo(str);
  return str;
}

bool
SerializationContext::hasKey(const String& key) {
  return jsonObject[key].success();
}

std::unique_ptr<Core::StatusResult>
SerializationContext::getStringValue(const String& key, String& value) {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return StatusResult::BadRequest("Key """ + key + """ is not defined.");

  if (!jsonVal.is<const char*>())
    return StatusResult::BadRequest("Value for key """ + key + """ should be a string.");

  value = (const char*)jsonVal;
  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
SerializationContext::getBoolValue(const String& key, bool& value) {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return StatusResult::BadRequest("Key """ + key + """ is not defined.");

  if (!jsonVal.is<bool>())
    return StatusResult::BadRequest("Value for key """ + key + """ should be a boolean.");

  value = (bool)jsonVal;
  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
SerializationContext::getEntity(const String& key, std::unique_ptr<Core::IEntity>& entity) {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return StatusResult::BadRequest("Key """ + key + """ is not defined.");

  if (!jsonVal.is<JsonObject>())
    return StatusResult::BadRequest("Value for key """ + key + """ should be a JSON object.");

  auto& nestedObject = jsonVal.asObject();
  SerializationContext context(serializationService, jsonBuffer, nestedObject);
  auto result = serializationService.deserialize(context, entity);
  if (!result->isOk()) {
      return StatusResult::InternalServerError(
        "Unable to deserialize a nested entity.", std::move(result));
  }
  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
SerializationContext::setValue(const String& key, const String& value) {
  jsonObject[key] = value;
  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
SerializationContext::setValue(const String& key, int value) {
  jsonObject[key] = value;
  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
SerializationContext::setValue(const String& key, bool value) {
  jsonObject[key] = value;
  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
SerializationContext::setValue(const String& key, const IList& list) {
  auto& array = jsonObject.createNestedArray(key);
  return list.forEach([&](const IEntity& element) {
    auto& nestedObject = array.createNestedObject();
    SerializationContext context(serializationService, jsonBuffer, nestedObject);
    auto result = serializationService.serialize(element, context);
    if (!result->isOk()) {
        return StatusResult::InternalServerError(
          "Unable to serialize an element of the list.", std::move(result));
    }
    return StatusResult::OK();
  });
}

std::unique_ptr<Core::StatusResult>
SerializationContext::setValue(const String& key, const Core::IEntity& entity) {
  auto& nestedObject = jsonObject.createNestedObject(key);
  SerializationContext context(serializationService, jsonBuffer, nestedObject);
  auto result = serializationService.serialize(entity, context);
  if (!result->isOk()) {
      return StatusResult::InternalServerError(
        "Unable to serialize a nested entity.", std::move(result));
  }
  return StatusResult::OK();
}
