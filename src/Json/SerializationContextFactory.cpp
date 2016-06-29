#include "SerializationContextFactory.hpp"

#include "SerializationContext.hpp"

#include "Core/Memory.hpp"

using namespace Json;
using namespace Core;

std::unique_ptr<Core::StatusResult>
SerializationContextFactory::create(
  const ISerializationService& serializationService,
  std::shared_ptr<ISerializationContext>& context) const {

  std::shared_ptr<DynamicJsonBuffer> jsonBuffer(
    std::make_shared<DynamicJsonBuffer>());
  JsonObject& jsonObject = jsonBuffer->createObject();

  context = make_unique<SerializationContext>(
    serializationService,
    jsonBuffer,
    jsonObject);
  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
SerializationContextFactory::create(
  const ISerializationService& serializationService,
  std::shared_ptr<ISerializationContext>& context,
  const String& json) const {

  std::shared_ptr<DynamicJsonBuffer> jsonBuffer(
    std::make_shared<DynamicJsonBuffer>());
  JsonObject& jsonObject = jsonBuffer->parseObject(json);
  if (!jsonObject.success())
    return StatusResult::BadRequest("Incorrect JSON format.");

  context = make_unique<SerializationContext>(
    serializationService,
    jsonBuffer,
    jsonObject);
  return StatusResult::OK();
}
