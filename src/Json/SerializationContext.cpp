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

std::string
SerializationContext::toString() const {
  std::string str;
  //jsonObject.printTo(str);
  return str;
}

bool
SerializationContext::hasKey(const std::string& key) {
  return jsonObject[key.c_str()].success();
}

Core::StatusResult::Unique
SerializationContext::getStringValue(const std::string& key, std::string& value) {

  auto jsonVal = jsonObject[key.c_str()];
  if (!jsonVal.success())
    return StatusResult::makeUnique(StatusCode::BadRequest, "Key """ + key + """ is not defined.");

  if (!jsonVal.is<const char*>())
    return StatusResult::makeUnique(StatusCode::BadRequest, "Value for key """ + key + """ should be a string.");

  value = (const char*)jsonVal;
  return StatusResult::OK();
}

Core::StatusResult::Unique
SerializationContext::getBoolValue(const std::string& key, bool& value) {

  auto jsonVal = jsonObject[key.c_str()];
  if (!jsonVal.success())
    return StatusResult::makeUnique(StatusCode::BadRequest, "Key """ + key + """ is not defined.");

  if (!jsonVal.is<bool>())
    return StatusResult::makeUnique(StatusCode::BadRequest, "Value for key """ + key + """ should be a boolean.");

  value = (bool)jsonVal;
  return StatusResult::OK();
}

Core::StatusResult::Unique
SerializationContext::getEntity(const std::string& key, Core::IEntity::Unique& entity) {

  auto jsonVal = jsonObject[key.c_str()];
  if (!jsonVal.success())
    return StatusResult::makeUnique(StatusCode::BadRequest, "Key """ + key + """ is not defined.");

  if (!jsonVal.is<JsonObject>())
    return StatusResult::makeUnique(StatusCode::BadRequest, "Value for key """ + key + """ should be a JSON object.");

  auto& nestedObject = jsonVal.asObject();
  SerializationContext context(serializationService, jsonBuffer, nestedObject);
  auto result = serializationService.deserialize(context, entity);
  if (!result->isOk()) {
    return StatusResult::makeUnique(StatusCode::InternalServerError,
      "Unable to deserialize a nested entity.", std::move(result));
  }
  return StatusResult::OK();
}

Core::StatusResult::Unique
SerializationContext::setValue(const std::string& key, const std::string& value) {
  jsonObject[key.c_str()] = value.c_str();
  return StatusResult::OK();
}

Core::StatusResult::Unique
SerializationContext::setValue(const std::string& key, int value) {
  jsonObject[key.c_str()] = value;
  return StatusResult::OK();
}

Core::StatusResult::Unique
SerializationContext::setValue(const std::string& key, bool value) {
  jsonObject[key.c_str()] = value;
  return StatusResult::OK();
}

Core::StatusResult::Unique
SerializationContext::setValue(const std::string& key, const IList& list) {
  auto& array = jsonObject.createNestedArray(key.c_str());
  return list.forEach([&](const IEntity& element) {
    auto& nestedObject = array.createNestedObject();
    SerializationContext context(serializationService, jsonBuffer, nestedObject);
    auto result = serializationService.serialize(element, context);
    if (!result->isOk()) {
      return StatusResult::makeUnique(StatusCode::InternalServerError,
        "Unable to serialize an element of the list.", std::move(result));
    }
    return StatusResult::OK();
  });
}

Core::StatusResult::Unique
SerializationContext::setValue(const std::string& key, const Core::IEntity& entity) {
  auto& nestedObject = jsonObject.createNestedObject(key.c_str());
  SerializationContext context(serializationService, jsonBuffer, nestedObject);
  auto result = serializationService.serialize(entity, context);
  if (!result->isOk()) {
      return StatusResult::makeUnique(StatusCode::InternalServerError,
        "Unable to serialize a nested entity.", std::move(result));
  }
  return StatusResult::OK();
}
