#include "ListSerializer.hpp"

#include "Models/Network.hpp"

using namespace Json;
using namespace Core;

std::unique_ptr<Core::IActionResult>
ListSerializer::serialize(
  const IList& list,
  ISerializationContext& context) const {

  context.setValue("elements", list);
  return StatusResult::OK();
}

std::unique_ptr<Core::IActionResult>
ListSerializer::deserialize(
  std::shared_ptr<IList>& list,
  ISerializationContext& context) const {

  return StatusResult::OK();
}
