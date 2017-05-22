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
DeserializationContext::hasKey(const std::string& key) const {
  return jsonObject[key].success();
}

std::tuple<Core::Status, std::string>
DeserializationContext::getString(const std::string& key) const {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return std::make_tuple(Status(StatusCode::BadRequest, "Key """ + key + """ is not defined."), "");

  if (!jsonVal.is<const char*>())
    return std::make_tuple(Status(StatusCode::BadRequest, "Value for key """ + key + """ should be a string."), "");

  return std::make_tuple(Status::OK, (const char*)jsonVal);
}

std::tuple<Core::Status, int>
DeserializationContext::getInt(const std::string& key) const {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return std::make_tuple(Status(StatusCode::BadRequest, "Key """ + key + """ is not defined."), 0);

  if (!jsonVal.is<int>())
    return std::make_tuple(Status(StatusCode::BadRequest, "Value for key """ + key + """ should be an int."), 0);

  return std::make_tuple(Status::OK, (int)jsonVal);
}

std::tuple<Core::Status, float>
DeserializationContext::getFloat(const std::string& key) const {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return std::make_tuple(Status(StatusCode::BadRequest, "Key """ + key + """ is not defined."), .0);

  if (!jsonVal.is<float>())
    return std::make_tuple(Status(StatusCode::BadRequest, "Value for key """ + key + """ should be an int."), .0);

  return std::make_tuple(Status::OK, (float)jsonVal);
}

std::tuple<Core::Status, bool>
DeserializationContext::getBool(const std::string& key) const {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return std::make_tuple(Status(StatusCode::BadRequest, "Key """ + key + """ is not defined."), false);

  if (!jsonVal.is<bool>())
    return std::make_tuple(Status(StatusCode::BadRequest, "Value for key """ + key + """ should be a boolean."), false);

  return std::make_tuple(Status::OK, (bool)jsonVal);
}

std::tuple<Core::Status, std::unique_ptr<Core::IEntity>>
DeserializationContext::getEntity(const std::string& key) const {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return std::make_tuple(Status(StatusCode::BadRequest, "Key """ + key + """ is not defined."), nullptr);

  if (!jsonVal.is<JsonObject>())
    return std::make_tuple(Status(StatusCode::BadRequest, "Value for key """ + key + """ should be a JSON object."), nullptr);

  auto& nestedObject = jsonVal.as<JsonObject>();
  DeserializationContext context(serializationService, jsonBuffer, nestedObject);
  auto result = serializationService.deserialize(context);
  if (!std::get<0>(result).isOk()) {
    return std::make_tuple(Status(StatusCode::InternalServerError,
      "Unable to deserialize a nested entity.", std::move(std::get<0>(result))), nullptr);
  }
  return result;
}
