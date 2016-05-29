#include "SerializationService.hpp"

using namespace Json;
using namespace Core;

void
SerializationService::serialize(const IEntity& entity,
                                const ISerializationContext& context) const {
  String type = entity.getTypeId();
  //const ISerializer& serializer = serializers[type];
  //serializer.serialize(entity, context);
}
