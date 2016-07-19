#include "ActionResult.hpp"

using namespace Core;

IActionResult::~IActionResult() {
}

StatusResult::Unique
StatusResult::OK() {
  return StatusResult::makeUnique(StatusCode::OK);
}

StatusResult::Unique
StatusResult::Created(String message) {
  return StatusResult::makeUnique(StatusCode::Created, message);
}

StatusResult::Unique
StatusResult::Accepted() {
  return StatusResult::makeUnique(StatusCode::Accepted);
}

StatusResult::Unique
StatusResult::NoContent(String message) {
  return StatusResult::makeUnique(StatusCode::NoContent, message);
}

StatusResult::Unique
StatusResult::Conflict(String message) {
  return StatusResult::makeUnique(StatusCode::Conflict, message);
}

StatusResult::Unique
StatusResult::BadRequest(String message) {
  return StatusResult::makeUnique(StatusCode::BadRequest, message);
}

StatusResult::Unique
StatusResult::BadRequest(String message,
  StatusResult::Unique innerResult) {
  return StatusResult::makeUnique(StatusCode::BadRequest, message, std::move(innerResult));
}

StatusResult::Unique
StatusResult::NotFound(String message) {
  return StatusResult::makeUnique(StatusCode::NotFound, message);
}

StatusResult::Unique
StatusResult::InternalServerError(String message) {
  return StatusResult::makeUnique(StatusCode::InternalServerError, message);
}

StatusResult::Unique
StatusResult::InternalServerError(String message,
  StatusResult::Unique innerResult) {
  return StatusResult::makeUnique(StatusCode::InternalServerError, message, std::move(innerResult));
}

StatusResult::Unique
StatusResult::NotImplemented() {
  return NotImplemented("Not implemented.");
}

StatusResult::Unique
StatusResult::NotImplemented(String message) {
  return StatusResult::makeUnique(StatusCode::NotImplemented, message);
}

RedirectResult::Unique
RedirectResult::ToRoute(String route) {
  return RedirectResult::makeUnique(route);
}
