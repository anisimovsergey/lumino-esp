#include "SerializationContextFactory.hpp"

#include "SerializationContext.hpp"

using namespace Json;
using namespace Core;

std::shared_ptr<Core::IActionResult>
SerializationContextFactory::create(
  const ISerializationService& serializationService,
  std::shared_ptr<ISerializationContext>& context) const {

  std::shared_ptr<DynamicJsonBuffer> jsonBuffer(new DynamicJsonBuffer);
  JsonObject& jsonObject = jsonBuffer->createObject();

  context = std::make_shared<SerializationContext>(
    serializationService,
    jsonBuffer,
    jsonObject);
  return StatusResult::OK();
}

std::shared_ptr<Core::IActionResult>
SerializationContextFactory::create(
  const ISerializationService& serializationService,
  std::shared_ptr<ISerializationContext>& context,
  const String& json) const {

  std::shared_ptr<DynamicJsonBuffer> jsonBuffer(new DynamicJsonBuffer);
  JsonObject& jsonObject = jsonBuffer->parseObject(json);
  if (!jsonObject.success())
    return StatusResult::BadRequest("Incorrect JSON format.");

  context = std::make_shared<SerializationContext>(
    serializationService,
    jsonBuffer,
    jsonObject);
  return StatusResult::OK();
}
