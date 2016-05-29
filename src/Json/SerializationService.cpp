#include "SerializationService.hpp"

#include <algorithm>

using namespace Json;
using namespace Core;

void
SerializationService::addSerializer(std::shared_ptr<ISerializer> serializer) {
  serializers.push_back(serializer);
}

void
SerializationService::serialize(const IEntity& entity,
                                ISerializationContext& context) const {
  String type = entity.getTypeId();
  auto findIter = std::find_if(serializers.begin(), serializers.end(),
    [&](std::shared_ptr<ISerializer> serializer){
      return serializer->getTypeId() == type;
    });

  if (findIter == serializers.end())
    return;

  (*findIter)->serialize(entity, context);
}
