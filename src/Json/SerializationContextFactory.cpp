#include "SerializationContextFactory.hpp"

#include "SerializationContext.hpp"

using namespace Json;
using namespace Core;

std::shared_ptr<ISerializationContext>
SerializationContextFactory::create(
  const ISerializationService& serializationService) const {
    return SerializationContext::create(serializationService);
}

Status
SerializationContextFactory::create(
  const ISerializationService& serializationService,
  const String& json,
  std::shared_ptr<ISerializationContext>& context) const {
    return SerializationContext::create(serializationService, json, context);
}
