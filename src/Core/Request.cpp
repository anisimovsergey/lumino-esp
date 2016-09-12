#include "Request.hpp"

using namespace Core;

Request::Request(ActionType actionType, std::string resource) :
 Message(actionType, resource, Priority::High) {
}

Request::Request(ActionType actionType, std::string resource,
  IEntity::Unique content) : Message(actionType, resource, Priority::High),
  content(std::move(content)) {
}
