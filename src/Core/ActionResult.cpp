#include "ActionResult.hpp"

using namespace Core;


std::shared_ptr<ActionResult>
ActionResult::Success() {
  return std::shared_ptr<ActionResult>(
    new ActionResult("Success", 200, "Success.", true));
}

std::shared_ptr<ActionResult>
ActionResult::Success(std::shared_ptr<IEntity> entity) {
  return std::shared_ptr<ActionResult>(
    new ActionResult("Success", 200, "Success.", true));
}

std::shared_ptr<ActionResult>
ActionResult::Conflict() {
  return std::shared_ptr<ActionResult>(
    new ActionResult("Conflict", 409, "Conflict."));
}

std::shared_ptr<ActionResult>
ActionResult::NotSupported() {
  return std::shared_ptr<ActionResult>(
    new ActionResult("NotSupported", 501, "Not supported"));
}

std::shared_ptr<ActionResult>
ActionResult::IncorrectObjectType() {
  return std::shared_ptr<ActionResult>(
    new ActionResult("IncorrectObjectType", 400, "Incorrect object type"));
}

std::shared_ptr<ActionResult>
ActionResult::UnableToParseJson() {
  return std::shared_ptr<ActionResult>(
    new ActionResult("UnableToParseJson", 400, "Unable to parse JSON."));
}

std::shared_ptr<ActionResult>
ActionResult::ValueIsNotAString() {
  return std::shared_ptr<ActionResult>(
    new ActionResult("ValueIsNotAString", 400, "Value is not a string."));
}

std::shared_ptr<ActionResult>
ActionResult::ValueIsNotABoolean() {
  return std::shared_ptr<ActionResult>(
    new ActionResult("ValueIsNotABoolean", 400, "Value is not a boolean."));
}

std::shared_ptr<ActionResult>
ActionResult::UnableToFindSerializer() {
  return std::shared_ptr<ActionResult>(
    new ActionResult("UnableToFindSerializer", 400, "Unable to find serializer."));
}

std::shared_ptr<ActionResult>
ActionResult::ResourceNotFound() {
  return std::shared_ptr<ActionResult>(
    new ActionResult("ResourceNotFound", 404, "Resource not found."));
}

std::shared_ptr<ActionResult>
ActionResult::ResourceCreated() {
  return std::shared_ptr<ActionResult>(
    new ActionResult("ResourceCreated", 302, "Resource created."));
}

std::shared_ptr<ActionResult>
ActionResult::RedirectTo(String newResource) {
  // TODO : Set Location header.
  return std::shared_ptr<ActionResult>(
    new ActionResult("ResourceCreated", 302, "Resource created."));
}

std::shared_ptr<ActionResult>
ActionResult::UnableToConnect() {
  return std::shared_ptr<ActionResult>(
    new ActionResult("UnableToConnect", 500, "Unable to connect."));
}

std::shared_ptr<ActionResult>
ActionResult::UnableToScanFiFiNetworks() {
  return std::shared_ptr<ActionResult>(
    new ActionResult("UnableToScanFiFiNetworks", 500, "Unable to scan FiFi networks."));
}

std::shared_ptr<ActionResult>
ActionResult::UnableToFindJsonKey(String key) {
  return std::shared_ptr<ActionResult>(
    new ActionResult("UnableToFindJsonKey", 400,
    "Unable to find JSON key """ + key + """."));
}

ActionResult::ActionResult(String id, int code, String title) :
  id(id), code(code), title(title), ok(false) {
}

ActionResult::ActionResult(String id, int code, String title, bool ok) :
  id(id), code(code), title(title), ok(ok) {
}
