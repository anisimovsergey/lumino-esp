#include "SerializationService.hpp"

#include <algorithm>

using namespace Json;
using namespace Core;

SerializationService::SerializationService(
  const ISerializationContextFactory& contextFactory) :
  contextFactory(contextFactory) {

}

String
SerializationService::serialize(const IEntity& entity) const {
  auto context = contextFactory.create(*this);
  serialize(entity, *context);
  return context->toString();
}

void
SerializationService::serialize(const IEntity& entity,
                                ISerializationContext& context) const {
  String type = entity.getTypeId();
  auto findIter = std::find_if(serializers.begin(), serializers.end(),
    [&](std::shared_ptr<const ISerializer> serializer){
      return serializer->getTypeId() == type;
    });

  if (findIter == serializers.end())
    return;

  (*findIter)->serialize(entity, context);
}

void
SerializationService::addSerializer(std::shared_ptr<const ISerializer> serializer) {
  serializers.push_back(serializer);
}
