#include "SerializationService.hpp"

#include "Core/Logger.hpp"

#include <algorithm>

using namespace Json;
using namespace Core;

#define TYPE_FIELD "type"

SerializationService::SerializationService(
  std::shared_ptr<const ISerializationContextFactory> contextFactory) :
  contextFactory(contextFactory) {
}

std::unique_ptr<Core::IActionResult>
SerializationService::serialize(
  const IEntity& entity,
  String& json) const {

  std::shared_ptr<ISerializationContext> context;
  Logger::message("Creating serialization context");
  auto actionResult = contextFactory->create(*this, context);
  if (!actionResult->isOk())
    return actionResult;

  Logger::message("Serialization context created");
  actionResult = serialize(entity, *context);
  if (!actionResult->isOk())
    return actionResult;

  Logger::message("Object serialized");
  json = context->toString();
  Logger::message("Context converted to string");
  return StatusResult::OK();
}

std::unique_ptr<Core::IActionResult>
SerializationService::serialize (
  const IEntity& entity,
  ISerializationContext& context) const {

  String typeId = entity.getTypeId();
  Logger::message("Getting serializer for type " + typeId);
  auto serializer = getSerialzier(typeId);
  if (!serializer)
    return StatusResult::BadRequest("Unable to find serializer for type """ +
      typeId + """.");

  Logger::message("Serializer found");
  context.setValue(TYPE_FIELD, typeId);
  return serializer->serialize(entity, context);
  Logger::message("Serializer used");
}

std::unique_ptr<Core::IActionResult>
SerializationService::deserialize(
  const String& json,
  std::shared_ptr<Core::IEntity>& entity) const {

  std::shared_ptr<ISerializationContext> context;
  auto actionResult = contextFactory->create(*this, context, json);
  if (!actionResult->isOk())
    return actionResult;

  String typeId;
  actionResult = context->getStringValue(TYPE_FIELD, typeId);
  if (!actionResult->isOk())
    return actionResult;

  auto serializer = getSerialzier(typeId);
  if (!serializer)
    return StatusResult::BadRequest("Unable to find serializer for type """ +
      typeId + """.");

  return serializer->deserialize(entity, *context);
}

void
SerializationService::addSerializer(
  std::shared_ptr<const ISerializer> serializer) {
  serializers.push_back(serializer);
}

std::shared_ptr<const ISerializer>
SerializationService::getSerialzier(String typeId) const {

  auto findIter = std::find_if(serializers.begin(), serializers.end(),
    [&](std::shared_ptr<const ISerializer> serializer){
      return serializer->getTypeId() == typeId;
    });

  if (findIter == serializers.end()) {
    Logger::message("Serializer not found for " + typeId);
    return nullptr;
  }

  return *findIter;
}
