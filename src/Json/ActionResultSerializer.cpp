#include "ActionResultSerializer.hpp"

using namespace Json;
using namespace Core;

std::shared_ptr<Core::ActionResult>
ActionResultSerializer::serialize(const ActionResult& actionResult,
                            ISerializationContext& context) const {

  context.setValue("code", actionResult.getCode());
  context.setValue("title", actionResult.getTitle());
  return ActionResult::Success();
}

std::shared_ptr<Core::ActionResult>
ActionResultSerializer::deserialize(
  std::shared_ptr<ActionResult>& actionResult,
  ISerializationContext& context) const {

  return ActionResult::NotSupported();
}
