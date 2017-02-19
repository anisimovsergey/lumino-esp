#include "ContextFactory.hpp"

#include "SerializationContext.hpp"
#include "DeserializationContext.hpp"

#include "Core/Memory.hpp"

using namespace Core;
using namespace Serialization;

Core::Status
ContextFactory::createSerializationContext(
  const ISerializationService& serializationService,
  std::unique_ptr<ISerializationContext>& context) const {

  std::shared_ptr<DynamicJsonBuffer> jsonBuffer(
    std::make_shared<DynamicJsonBuffer>());
  JsonObject& jsonObject = jsonBuffer->createObject();

  context = std::make_unique<SerializationContext>(
    serializationService,
    jsonBuffer,
    jsonObject);
  return Status::OK;
}

Core::Status
ContextFactory::createDeserializationContext(
  const ISerializationService& serializationService, const std::string& json,
  std::unique_ptr<IDeserializationContext>& context) const {

  std::shared_ptr<DynamicJsonBuffer> jsonBuffer(
    std::make_shared<DynamicJsonBuffer>());
  JsonObject& jsonObject = jsonBuffer->parseObject(json.c_str());
  if (!jsonObject.success())
    return Status(StatusCode::BadRequest, "Incorrect JSON format.");

  context = std::make_unique<DeserializationContext>(
    serializationService,
    jsonBuffer,
    jsonObject);
  return Status::OK;
}
