#include "SerializationContextFactory.hpp"

#include "SerializationContext.hpp"

using namespace Json;
using namespace Core;

Core::Status
SerializationContextFactory::create(
  const ISerializationService& serializationService,
  std::shared_ptr<ISerializationContext>& context) const {
    return SerializationContext::create(serializationService, context);
}

Status
SerializationContextFactory::create(
  const ISerializationService& serializationService,
  std::shared_ptr<ISerializationContext>& context,
  const String& json) const {
    return SerializationContext::create(serializationService, context, json);
}
