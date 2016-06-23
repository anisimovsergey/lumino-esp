#include "ActionResult.hpp"

using namespace Core;

std::unique_ptr<IActionResult>
StatusResult::OK() {
  return make_unique<StatusResult>(StatusCode::OK);
}

std::unique_ptr<IActionResult>
StatusResult::Conflict(String message) {
  return make_unique<StatusResult>(StatusCode::Conflict, message);
}

std::unique_ptr<IActionResult>
StatusResult::BadRequest(String message) {
  return make_unique<StatusResult>(StatusCode::BadRequest, message);
}

std::unique_ptr<IActionResult>
StatusResult::NotFound(String message) {
  return make_unique<StatusResult>(StatusCode::NotFound, message);
}

std::unique_ptr<IActionResult>
StatusResult::InternalServerError(String message) {
  return make_unique<StatusResult>(StatusCode::InternalServerError, message);
}

std::unique_ptr<IActionResult>
StatusResult::NotImplemented() {
  return NotImplemented("Not implemented.");
}

std::unique_ptr<IActionResult>
StatusResult::NotImplemented(String message) {
  return make_unique<StatusResult>(StatusCode::NotImplemented, message);
}

std::unique_ptr<IActionResult>
RedirectResult::ToRoute(String route) {
  return make_unique<RedirectResult>(route);
}

std::unique_ptr<IActionResult>
ObjectResult::OK(std::shared_ptr<IEntity> entity) {
  return make_unique<ObjectResult>(entity);
}
