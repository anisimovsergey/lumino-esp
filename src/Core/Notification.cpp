#include "Notification.hpp"

using namespace Core;

Notification::Notification(ActionType actionType, std::string resource,
  IEntity::Shared result) : Message(actionType, resource, Priority::Low),
  result(result) {
}
