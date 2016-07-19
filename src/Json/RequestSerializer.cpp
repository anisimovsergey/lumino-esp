#include "RequestSerializer.hpp"

using namespace Core;
using namespace Json;

#define FIELD_ACTION "action"
#define FIELD_RESOURCE "resource"
#define FIELD_CONTENT "content"

std::unique_ptr<Core::StatusResult>
RequestSerializer::serialize(
  const Request& request,
  ISerializationContext& context) const {
  return StatusResult::NotImplemented();
}

std::unique_ptr<Core::StatusResult>
RequestSerializer::deserialize(
  std::unique_ptr<Request>& request,
  ISerializationContext& context) const {

  String actionTypeStr;
  auto result = context.getStringValue(FIELD_ACTION, actionTypeStr);
  if (!result->isOk())
    return result;

  ActionType actionType = ActionType::getById(actionTypeStr);
  if (actionType == ActionType::Unknown)
    return StatusResult::BadRequest("Action type '" + actionTypeStr + "' is not supported.");

  String resource;
  result = context.getStringValue(FIELD_RESOURCE, resource);
  if (!result->isOk())
    return result;

  std::unique_ptr<Core::IEntity> content;
  if (context.hasKey(FIELD_CONTENT)) {
    result = context.getEntity(FIELD_CONTENT, content);
    if (!result->isOk())
      return result;
  }

  request = Request::makeUnique(actionType, resource, std::move(content));
  return StatusResult::OK();
}
