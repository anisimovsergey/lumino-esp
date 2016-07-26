#include "SerializationService.hpp"

#include <algorithm>

using namespace Json;
using namespace Core;

#define TYPE_FIELD "type"

SerializationService::SerializationService(
  std::shared_ptr<const ISerializationContextFactory> contextFactory) :
  contextFactory(contextFactory) {
}

std::unique_ptr<Core::StatusResult>
SerializationService::serialize(
  const IEntity& entity,
  String& json) const {

  std::unique_ptr<ISerializationContext> context;
  auto result = contextFactory->create(*this, context);
  if (!result->isOk())
    return result;

  result = serialize(entity, *context);
  if (!result->isOk())
    return result;

  json = context->toString();
  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
SerializationService::serialize (
  const IEntity& entity,
  ISerializationContext& context) const {

  String typeId = entity.getTypeId();
  auto serializer = getSerialzier(typeId);
  if (!serializer) {
    return StatusResult::makeUnique(StatusCode::BadRequest,
      "Unable to find a serializer for type """ + typeId + """.");
  }
  context.setValue(TYPE_FIELD, typeId);
  return serializer->serialize(entity, context);
}

std::unique_ptr<Core::StatusResult>
SerializationService::deserialize(
  const String& json,
  std::unique_ptr<Core::IEntity>& entity) const {

  std::unique_ptr<ISerializationContext> context;
  auto actionResult = contextFactory->create(*this, json, context);
  if (!actionResult->isOk())
    return actionResult;

  return deserialize(*context, entity);
}

std::unique_ptr<Core::StatusResult>
SerializationService::deserialize(
  ISerializationContext& context,
  std::unique_ptr<Core::IEntity>& entity) const {

  String typeId;
  auto actionResult = context.getStringValue(TYPE_FIELD, typeId);
  if (!actionResult->isOk())
    return actionResult;

  auto serializer = getSerialzier(typeId);
  if (!serializer) {
    return StatusResult::makeUnique(StatusCode::BadRequest,
      "Unable to find serializer for type """ + typeId + """.");
  }
  return serializer->deserialize(entity, context);
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

  if (findIter == serializers.end())
    return nullptr;

  return *findIter;
}
