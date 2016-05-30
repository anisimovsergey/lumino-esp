#include "SerializationContextFactory.hpp"

#include "SerializationContext.hpp"

using namespace Json;

std::shared_ptr<ISerializationContext>
SerializationContextFactory::create(
  const ISerializationService& serializationService) const {
    return SerializationContext::create(serializationService);
}
