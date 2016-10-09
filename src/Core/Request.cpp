#include "Request.hpp"

using namespace Core;

Request::Request(std::string sender, std::string receiver,
  ActionType actionType, std::string resource) :
  Message(sender, receiver, actionType, resource, Priority::High) {
}

Request::Request(std::string sender, std::string receiver,
  ActionType actionType, std::string resource, IEntity::Unique content) :
  Message(sender, receiver, actionType, resource, Priority::High),
  content(std::move(content)) {
}
