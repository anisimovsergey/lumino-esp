#include "StatusResultSerializer.hpp"

using namespace Json;
using namespace Core;

#define FIELD_CODE "code"
#define FIELD_MESSAGE "message"
#define FIELD_INNER_RESULT "innerResult"

Core::StatusResult::Unique
StatusResultSerializer::serialize(const StatusResult& statusResult,
                            ISerializationContext& context) const {

  auto result = context.setValue(FIELD_CODE, (int)statusResult.getStatusCode());
  if (!result->isOk())
    return result;

  result =context.setValue(FIELD_MESSAGE, statusResult.getMessage());
  if (!result->isOk())
    return result;

  auto innerResult = statusResult.getInnerReuslt();
  if (innerResult != nullptr) {
    result = context.setValue(FIELD_INNER_RESULT, *innerResult);
    if (!result->isOk())
      return result;
  }

  return StatusResult::OK();
}

Core::StatusResult::Unique
StatusResultSerializer::deserialize(
  StatusResult::Unique& statusResult,
  ISerializationContext& context) const {

  return StatusResult::NotImplemented();
}
