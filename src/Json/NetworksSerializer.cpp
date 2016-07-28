#include "NetworksSerializer.hpp"

using namespace Json;
using namespace Core;

#define FIELD_ELEMENTS "elements"

Core::StatusResult::Unique
NetworksSerializer::serialize(const Models::Networks& networks,
  ISerializationContext& context) const {

  auto result = context.setValue(FIELD_ELEMENTS, networks);
  if (!result->isOk())
    return result;

  return StatusResult::OK();
}

Core::StatusResult::Unique
NetworksSerializer::deserialize(Models::Networks::Unique& networks,
  ISerializationContext& context) const {

  return StatusResult::NotImplemented();
}
