#include "ListSerializer.hpp"

#include "Models/Network.hpp"

using namespace Json;
using namespace Core;

std::shared_ptr<Core::ActionResult>
ListSerializer::serialize(
  const IList& list,
  ISerializationContext& context) const {

  context.setValue("elements", list);
  return ActionResult::Success();
}

std::shared_ptr<Core::ActionResult>
ListSerializer::deserialize(
  std::shared_ptr<IList>& list,
  ISerializationContext& context) const {

  return ActionResult::NotSupported();
}
