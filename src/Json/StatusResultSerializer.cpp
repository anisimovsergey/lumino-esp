#include "StatusResultSerializer.hpp"

using namespace Json;
using namespace Core;

std::unique_ptr<Core::IActionResult>
StatusResultSerializer::serialize(const StatusResult& statusResult,
                            ISerializationContext& context) const {

  context.setValue("code", statusResult.getStatusCode().getCode());
  context.setValue("text", statusResult.getStatusCode().getText());
  context.setValue("message", statusResult.getMessage());
  return StatusResult::OK();
}

std::unique_ptr<Core::IActionResult>
StatusResultSerializer::deserialize(
  std::shared_ptr<StatusResult>& statusResult,
  ISerializationContext& context) const {

  return StatusResult::NotImplemented();
}
