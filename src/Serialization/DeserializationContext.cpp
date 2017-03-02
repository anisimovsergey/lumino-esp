#include "DeserializationContext.hpp"

#include "Serialization/ISerializationService.hpp"

using namespace Core;
using namespace Serialization;

DeserializationContext::DeserializationContext(
  const ISerializationService& serializationService,
  std::shared_ptr<const DynamicJsonBuffer> jsonBuffer,
  JsonObject& jsonObject) :
    serializationService(serializationService),
    jsonBuffer(jsonBuffer),
    jsonObject(jsonObject) {
}

bool
DeserializationContext::hasKey(const std::string& key) {
  return jsonObject[key].success();
}

Core::Status
DeserializationContext::getString(const std::string& key, std::string& value) {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return Status(StatusCode::BadRequest, "Key """ + key + """ is not defined.");

  if (!jsonVal.is<const char*>())
    return Status(StatusCode::BadRequest, "Value for key """ + key + """ should be a string.");

  value = (const char*)jsonVal;
  return Status::OK;
}

Core::Status
DeserializationContext::getBool(const std::string& key, bool& value) {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return Status(StatusCode::BadRequest, "Key """ + key + """ is not defined.");

  if (!jsonVal.is<bool>())
    return Status(StatusCode::BadRequest, "Value for key """ + key + """ should be a boolean.");

  value = (bool)jsonVal;
  return Status::OK;
}

Core::Status
DeserializationContext::getInt(const std::string& key, int& value) {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return Status(StatusCode::BadRequest, "Key """ + key + """ is not defined.");

  if (!jsonVal.is<int>())
    return Status(StatusCode::BadRequest, "Value for key """ + key + """ should be an int.");

  value = (int)jsonVal;
  return Status::OK;
}

Core::Status
DeserializationContext::getEntity(const std::string& key, std::unique_ptr<Core::IEntity>& entity) {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return Status(StatusCode::BadRequest, "Key """ + key + """ is not defined.");

  if (!jsonVal.is<JsonObject>())
    return Status(StatusCode::BadRequest, "Value for key """ + key + """ should be a JSON object.");

  auto& nestedObject = jsonVal.as<JsonObject>();
  DeserializationContext context(serializationService, jsonBuffer, nestedObject);
  auto result = serializationService.deserialize(context, entity);
  if (!result.isOk()) {
    return Status(StatusCode::InternalServerError,
      "Unable to deserialize a nested entity.", std::move(result));
  }
  return Status::OK;
}
