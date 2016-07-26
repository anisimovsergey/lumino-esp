#include "StatusResult.hpp"

using namespace Core;

StatusResult::Unique
StatusResult::OK() {
  return StatusResult::makeUnique(StatusCode::OK, "OK");
}

StatusResult::Unique
StatusResult::NotImplemented() {
  return StatusResult::makeUnique(StatusCode::NotImplemented, "Not implemented.");
}

StatusResult::StatusResult(const StatusCode& statusCode, const String& message) :
  statusCode(statusCode), message(message) {
}

StatusResult::StatusResult(const StatusCode& statusCode, const String& message,
             StatusResult::Unique innerResult) :
  statusCode(statusCode), message(message), innerResult(std::move(innerResult)) {
}
