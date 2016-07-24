#include "NotificationSerializer.hpp"

using namespace Core;
using namespace Json;

#define FIELD_ACTION "action"
#define FIELD_RESOURCE "resource"
#define FIELD_CONTENT "content"

std::unique_ptr<Core::StatusResult>
NotificationSerializer::serialize(
  const Notification& notification,
  ISerializationContext& context) const {

  auto result = context.setValue(FIELD_ACTION, notification.getActionType().getId());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_RESOURCE, notification.getResource());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_CONTENT, notification.getContent());
  if (!result->isOk())
    return result;

  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
NotificationSerializer::deserialize(
  std::unique_ptr<Notification>& notification,
  ISerializationContext& context) const {

  return StatusResult::NotImplemented();
}
