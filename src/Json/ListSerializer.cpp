#include "ListSerializer.hpp"

#include "Models/Network.hpp"

using namespace Json;
using namespace Core;

#define FIELD_ELEMENTS "elements"

Core::StatusResult::Unique
ListSerializer::serialize(
  const IList& list,
  ISerializationContext& context) const {

  auto result = context.setValue(FIELD_ELEMENTS, list);
  if (!result->isOk())
    return result;

  return StatusResult::OK();
}

Core::StatusResult::Unique
ListSerializer::deserialize(
  IList::Unique& list,
  ISerializationContext& context) const {

  return StatusResult::NotImplemented();
}
