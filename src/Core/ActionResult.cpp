#include "ActionResult.hpp"

using namespace Core;

IActionResult::~IActionResult() {
}

std::unique_ptr<StatusResult>
StatusResult::OK() {
  return make_unique<StatusResult>(StatusCode::OK);
}

std::unique_ptr<StatusResult>
StatusResult::Created(String message) {
  return make_unique<StatusResult>(StatusCode::Created, message);
}

std::unique_ptr<StatusResult>
StatusResult::Accepted() {
  return make_unique<StatusResult>(StatusCode::Accepted);
}

std::unique_ptr<StatusResult>
StatusResult::NoContent(String message) {
  return make_unique<StatusResult>(StatusCode::NoContent, message);
}

std::unique_ptr<StatusResult>
StatusResult::Conflict(String message) {
  return make_unique<StatusResult>(StatusCode::Conflict, message);
}

std::unique_ptr<StatusResult>
StatusResult::BadRequest(String message) {
  return make_unique<StatusResult>(StatusCode::BadRequest, message);
}

std::unique_ptr<StatusResult>
StatusResult::BadRequest(String message,
  std::unique_ptr<StatusResult> innerResult) {
  return make_unique<StatusResult>(StatusCode::BadRequest, message, std::move(innerResult));
}

std::unique_ptr<StatusResult>
StatusResult::NotFound(String message) {
  return make_unique<StatusResult>(StatusCode::NotFound, message);
}

std::unique_ptr<StatusResult>
StatusResult::InternalServerError(String message) {
  return make_unique<StatusResult>(StatusCode::InternalServerError, message);
}

std::unique_ptr<StatusResult>
StatusResult::InternalServerError(String message,
  std::unique_ptr<StatusResult> innerResult) {
  return make_unique<StatusResult>(StatusCode::InternalServerError, message, std::move(innerResult));
}

std::unique_ptr<StatusResult>
StatusResult::NotImplemented() {
  return NotImplemented("Not implemented.");
}

std::unique_ptr<StatusResult>
StatusResult::NotImplemented(String message) {
  return make_unique<StatusResult>(StatusCode::NotImplemented, message);
}

std::unique_ptr<RedirectResult>
RedirectResult::ToRoute(String route) {
  return make_unique<RedirectResult>(route);
}
