#include "Notification.hpp"

using namespace Core;

Notification::Notification(ActionType actionType, std::string resource,
  IEntity::Unique result) : Message(actionType, resource, Priority::Low),
  result(std::move(result)) {
}
