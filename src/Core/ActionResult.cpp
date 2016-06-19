#include "ActionResult.hpp"

using namespace Core;

std::shared_ptr<IActionResult>
StatusResult::OK() {
  return std::shared_ptr<IActionResult>(
    new StatusResult(StatusCode::OK));
}

std::shared_ptr<IActionResult>
StatusResult::Conflict(String message) {
  return std::shared_ptr<IActionResult>(
    new StatusResult(StatusCode::Conflict, message));
}

std::shared_ptr<IActionResult>
StatusResult::BadRequest(String message) {
  return std::shared_ptr<IActionResult>(
    new StatusResult(StatusCode::BadRequest, message));
}

std::shared_ptr<IActionResult>
StatusResult::NotFound(String message) {
  return std::shared_ptr<IActionResult>(
    new StatusResult(StatusCode::NotFound, message));
}

std::shared_ptr<IActionResult>
StatusResult::InternalServerError(String message) {
  return std::shared_ptr<IActionResult>(
    new StatusResult(StatusCode::InternalServerError, message));
}

std::shared_ptr<IActionResult>
StatusResult::NotImplemented() {
  return NotImplemented("Not implemented.");
}

std::shared_ptr<IActionResult>
StatusResult::NotImplemented(String message) {
  return std::shared_ptr<IActionResult>(
    new StatusResult(StatusCode::NotImplemented, message));
}

std::shared_ptr<IActionResult>
RedirectResult::ToRoute(String route) {
  return std::shared_ptr<IActionResult>(
    new RedirectResult(route));
}

std::shared_ptr<IActionResult>
ObjectResult::OK(std::shared_ptr<IEntity> entity) {
  return std::shared_ptr<IActionResult>(
    new ObjectResult(entity));
}
