#include "StatusResultSerializer.hpp"

using namespace Json;
using namespace Core;

#define FIELD_CODE "code"
#define FIELD_TEXT "text"
#define FIELD_MESSAGE "message"
#define FIELD_INNER_RESULT "innerResult"

std::unique_ptr<Core::StatusResult>
StatusResultSerializer::serialize(const StatusResult& statusResult,
                            ISerializationContext& context) const {

  auto result = context.setValue(FIELD_CODE,
    statusResult.getStatusCode().getCode());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_TEXT,
    statusResult.getStatusCode().getText());
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

std::unique_ptr<Core::StatusResult>
StatusResultSerializer::deserialize(
  std::unique_ptr<StatusResult>& statusResult,
  ISerializationContext& context) const {

  return StatusResult::NotImplemented();
}
