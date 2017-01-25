#include "ContextFactory.hpp"

#include "SerializationContext.hpp"
#include "DeserializationContext.hpp"

#include "Core/Memory.hpp"

using namespace Core;
using namespace Serialization;

Core::Status
ContextFactory::createSerializationContext(
  const ISerializationService& serializationService,
  ISerializationContext::Unique& context) const {

  std::shared_ptr<DynamicJsonBuffer> jsonBuffer(
    std::make_shared<DynamicJsonBuffer>());
  JsonObject& jsonObject = jsonBuffer->createObject();

  context = SerializationContext::makeUnique(
    serializationService,
    jsonBuffer,
    jsonObject);
  return Status::OK;
}

Core::Status
ContextFactory::createDeserializationContext(
  const ISerializationService& serializationService, const std::string& json,
  IDeserializationContext::Unique& context) const {

  std::shared_ptr<DynamicJsonBuffer> jsonBuffer(
    std::make_shared<DynamicJsonBuffer>());
  JsonObject& jsonObject = jsonBuffer->parseObject(json.c_str());
  if (!jsonObject.success())
    return Status(StatusCode::BadRequest, "Incorrect JSON format.");

  context = DeserializationContext::makeUnique(
    serializationService,
    jsonBuffer,
    jsonObject);
  return Status::OK;
}
