#include "ListSerializer.hpp"

#include "Models/Network.hpp"

using namespace Json;
using namespace Core;

#define FIELD_ELEMENTS "elements"

std::unique_ptr<Core::StatusResult>
ListSerializer::serialize(
  const IList& list,
  ISerializationContext& context) const {

  auto result = context.setValue(FIELD_ELEMENTS, list);
  if (!result->isOk())
    return result;

  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
ListSerializer::deserialize(
  std::unique_ptr<IList>& list,
  ISerializationContext& context) const {

  return StatusResult::NotImplemented();
}
