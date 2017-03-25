#include "ContextFactory.hpp"

#include "SerializationContext.hpp"
#include "DeserializationContext.hpp"

#include "Core/Memory.hpp"

using namespace Core;
using namespace Serialization;

std::tuple<Core::Status, std::unique_ptr<ISerializationContext>>
ContextFactory::createSerializationContext(
  const ISerializationService& serializationService) const {

  std::shared_ptr<DynamicJsonBuffer> jsonBuffer(
    std::make_shared<DynamicJsonBuffer>());
  JsonObject& jsonObject = jsonBuffer->createObject();

  auto context = std::make_unique<SerializationContext>(
    serializationService,
    jsonBuffer,
    jsonObject);
  return std::make_tuple(Status::OK, std::move(context));
}

std::tuple<Core::Status, std::unique_ptr<IDeserializationContext>>
ContextFactory::createDeserializationContext(
  const ISerializationService& serializationService, const std::string& json) const {

  std::shared_ptr<DynamicJsonBuffer> jsonBuffer(
    std::make_shared<DynamicJsonBuffer>());
  JsonObject& jsonObject = jsonBuffer->parseObject(json.c_str());
  if (!jsonObject.success())
    return std::make_tuple(Status(StatusCode::BadRequest, "Incorrect JSON format."), nullptr);

  auto context = std::make_unique<DeserializationContext>(
    serializationService,
    jsonBuffer,
    jsonObject);
  return std::make_tuple(Status::OK, std::move(context));
}
