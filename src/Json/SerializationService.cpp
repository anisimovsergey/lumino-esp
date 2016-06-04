#include "SerializationService.hpp"

#include <algorithm>

using namespace Json;
using namespace Core;

SerializationService::SerializationService(
  std::shared_ptr<const ISerializationContextFactory> contextFactory) :
  contextFactory(contextFactory) {
}

String
SerializationService::serialize(
  const IEntity& entity) const {

  auto context = contextFactory->create(*this);
  serialize(entity, *context);
  return context->toString();
}

void
SerializationService::serialize (
  const IEntity& entity,
  ISerializationContext& context) const {

  String typeId = entity.getTypeId();
  auto serializer = getSerialzier(typeId);
  if (serializer == nullptr)
    return; // Must return status

  context.setValue("type", typeId);
  serializer->serialize(entity, context);
}

Status
SerializationService::deserialize(
  const String& json,
  std::shared_ptr<Core::IEntity>& entity) const {

  std::shared_ptr<ISerializationContext> context;
  Status status = contextFactory->create(*this, json, context);
  if (!status.isOk())
    return status;

  String typeId;
  status = context->getStringValue("type", typeId);
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
