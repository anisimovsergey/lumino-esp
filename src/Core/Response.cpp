#include "Response.hpp"

using namespace Core;

Response::Response(ActionType actionType, std::string resource,
  ActionResult::Unique result) : Message(actionType, resource, Priority::Mid),
  result(std::move(result)) {
}
