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

Core::Status
SerializationService::serialize(
  const IEntity& entity,
  String& json) const {

  std::shared_ptr<ISerializationContext> context;
  Status status = contextFactory->create(*this, context);
  if (!status.isOk())
    return status;
  Logger::message("Serialization context created");
  status = serialize(entity, *context);
  if (!status.isOk())
    return status;
  Logger::message("Object serialized");
  json = context->toString();
  Logger::message("Context converted to string");
  return Status::Ok;
}

Core::Status
SerializationService::serialize (
  const IEntity& entity,
  ISerializationContext& context) const {

  String typeId = entity.getTypeId();
  Logger::message("Getting serializer for type " + typeId);
  auto serializer = getSerialzier(typeId);
  if (serializer == nullptr)
    return Status::UnableToFindSerializer;
  Logger::message("Serializer found");
  context.setValue(TYPE_FIELD, typeId);
  return serializer->serialize(entity, context);
  Logger::message("Serializer used");
}

Status
SerializationService::deserialize(
  const String& json,
  std::shared_ptr<Core::IEntity>& entity) const {

  std::shared_ptr<ISerializationContext> context;
  Status status = contextFactory->create(*this, context, json);
  if (!status.isOk())
    return status;

  String typeId;
  status = context->getStringValue(TYPE_FIELD, typeId);
  if (!status.isOk())
    return status;

  auto serializer = getSerialzier(typeId);
  if (serializer == nullptr)
    return Status::UnableToFindSerializer;

  return serializer->deserialize(entity, *context);
}

void
SerializationService::addSerializer(
  std::shared_ptr<const ISerializer> serializer) {
  serializers.push_back(serializer);
}

const ISerializer*
SerializationService::getSerialzier(
  const String& typeId) const {

  auto findIter = std::find_if(serializers.begin(), serializers.end(),
    [&](std::shared_ptr<const ISerializer> serializer){
      return serializer->getTypeId() == typeId;
    });

  if (findIter == serializers.end())
    return nullptr;

  return findIter->get();
}
