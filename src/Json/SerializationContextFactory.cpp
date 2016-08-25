#include "SerializationContextFactory.hpp"

#include "SerializationContext.hpp"

#include "Core/Memory.hpp"

using namespace Json;
using namespace Core;

Core::StatusResult::Unique
SerializationContextFactory::create(
  const ISerializationService& serializationService,
  ISerializationContext::Unique& context) const {

  std::shared_ptr<DynamicJsonBuffer> jsonBuffer(
    std::make_shared<DynamicJsonBuffer>());
  JsonObject& jsonObject = jsonBuffer->createObject();

  context = SerializationContext::makeUnique(
    serializationService,
    jsonBuffer,
    jsonObject);
  return StatusResult::OK();
}

Core::StatusResult::Unique
SerializationContextFactory::create(
  const ISerializationService& serializationService, const std::string& json,
  ISerializationContext::Unique& context) const {

  std::shared_ptr<DynamicJsonBuffer> jsonBuffer(
    std::make_shared<DynamicJsonBuffer>());
  JsonObject& jsonObject = jsonBuffer->parseObject(json.c_str());
  if (!jsonObject.success())
    return StatusResult::makeUnique(StatusCode::BadRequest, "Incorrect JSON format.");

  context = SerializationContext::makeUnique(
    serializationService,
    jsonBuffer,
    jsonObject);
  return StatusResult::OK();
}
