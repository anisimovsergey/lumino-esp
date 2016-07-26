// Copyright Sergey Anisimov 2016-2017

// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_STATUS_RESULT_HPP
#define CORE_STATUS_RESULT_HPP

#include "ActionResult.hpp"

namespace Core {

class StatusResult : public ActionResult {
TYPE_INFO(StatusResult, ActionResult, "statusResult")
public:
  static StatusResult::Unique OK();
  static StatusResult::Unique Created(String message);
  static StatusResult::Unique Accepted();
  static StatusResult::Unique NoContent(String message);
  static StatusResult::Unique Conflict(String message);
  static StatusResult::Unique BadRequest(String message);
  static StatusResult::Unique BadRequest(String message, StatusResult::Unique innerResult);
  static StatusResult::Unique NotFound(String message);
  static StatusResult::Unique InternalServerError(String message);
  static StatusResult::Unique InternalServerError(String message, StatusResult::Unique innerResult);
  static StatusResult::Unique NotImplemented();
  static StatusResult::Unique NotImplemented(String message);

  StatusResult(const StatusCode& statusCode) : statusCode(statusCode) {}

  StatusResult(const StatusCode& statusCode, String message) : statusCode(
      statusCode), message(message) {}

  StatusResult(const StatusCode   & statusCode,
               String               message,
               StatusResult::Unique innerResult) : statusCode(statusCode),
    message(message),
    innerResult(std::move(innerResult)) {}

  // From ActionResult
  virtual StatusCode getStatusCode() const override {
    return statusCode;
  }

  bool isOk() const {
    return getStatusCode() == StatusCode::OK;
  }

  String getMessage() const {
    return message;
  }

  const StatusResult* getInnerReuslt() const {
    return innerResult.get();
  }

private:

  const StatusCode statusCode;
  const String     message;
  const StatusResult::Unique innerResult;
};

}

#endif /* end of include guard: CORE_ACTION_RESULT_HPP */
