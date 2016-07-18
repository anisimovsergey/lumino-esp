#include "ObjectResultSerializer.hpp"

using namespace Core;
using namespace Json;

#define FIELD_CODE "code"
#define FIELD_TEXT "text"
#define FIELD_OBJECT "object"

std::unique_ptr<Core::StatusResult>
ObjectResultSerializer::serialize(
  const ObjectResult& objectResult,
  ISerializationContext& context) const {

  auto result = context.setValue(FIELD_CODE,
    objectResult.getStatusCode().getCode());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_TEXT,
    objectResult.getStatusCode().getText());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_OBJECT, objectResult.getObject());
  if (!result->isOk())
    return result;

  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
ObjectResultSerializer::deserialize(
  std::unique_ptr<ObjectResult>& objectResult,
  ISerializationContext& context) const {

  return StatusResult::NotImplemented();
}
