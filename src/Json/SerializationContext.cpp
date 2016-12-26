#include "SerializationContext.hpp"

#include "Core/Logger.hpp"

using namespace Json;
using namespace Core;

namespace {

  class StringBuilder : public Print {
   public:
    StringBuilder(std::string &str) : str(str) {}

    virtual size_t write(uint8_t c) {
      str += static_cast<char>(c);
      return 1;
    }

   private:
    StringBuilder &operator=(const StringBuilder &);

    std::string &str;
  };

}

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
  str.reserve(jsonObject.measureLength());
  StringBuilder strBuilder(str);
  jsonObject.printTo(strBuilder);
  return str;
}

bool
SerializationContext::hasKey(const std::string& key) {
  return jsonObject[key].success();
}

Core::StatusResult::Unique
SerializationContext::getStringValue(const std::string& key, std::string& value) {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return StatusResult::makeUnique(StatusCode::BadRequest, "Key """ + key + """ is not defined.");

  if (!jsonVal.is<const char*>())
    return StatusResult::makeUnique(StatusCode::BadRequest, "Value for key """ + key + """ should be a string.");

  value = (const char*)jsonVal;
  return StatusResult::OK();
}

Core::StatusResult::Unique
SerializationContext::getIntValue(const std::string& key, int& value) {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return StatusResult::makeUnique(StatusCode::BadRequest, "Key """ + key + """ is not defined.");

  if (!jsonVal.is<int>())
    return StatusResult::makeUnique(StatusCode::BadRequest, "Value for key """ + key + """ should be a integer.");

  value = (int)jsonVal;
  return StatusResult::OK();
}

Core::StatusResult::Unique
SerializationContext::getBoolValue(const std::string& key, bool& value) {

  auto jsonVal = jsonObject[key];
  if (!jsonVal.success())
    return StatusResult::makeUnique(StatusCode::BadRequest, "Key """ + key + """ is not defined.");

  if (!jsonVal.is<bool>())
    return StatusResult::makeUnique(StatusCode::BadRequest, "Value for key """ + key + """ should be a boolean.");

  value = (bool)jsonVal;
  return StatusResult::OK();
}

Core::StatusResult::Unique
SerializationContext::getEntity(const std::string& key, Core::IEntity::Unique& entity) {

  auto jsonVal = jsonObject[key];
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
  jsonObject[key] = value;
  return StatusResult::OK();
}

Core::StatusResult::Unique
SerializationContext::setValue(const std::string& key, int value) {
  jsonObject[key] = value;
  return StatusResult::OK();
}

Core::StatusResult::Unique
SerializationContext::setValue(const std::string& key, bool value) {
  jsonObject[key] = value;
  return StatusResult::OK();
}

Core::StatusResult::Unique
SerializationContext::setValue(const std::string& key, const IList& list) {
  auto& array = jsonObject.createNestedArray(key);
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
  auto& nestedObject = jsonObject.createNestedObject(key);
  SerializationContext context(serializationService, jsonBuffer, nestedObject);
  auto result = serializationService.serialize(entity, context);
  if (!result->isOk()) {
      return StatusResult::makeUnique(StatusCode::InternalServerError,
        "Unable to serialize a nested entity.", std::move(result));
  }
  return StatusResult::OK();
}
