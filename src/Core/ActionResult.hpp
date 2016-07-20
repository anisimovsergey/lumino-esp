// Copyright Sergey Anisimov 2016-2017

// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_ACTION_RESULT_HPP
#define CORE_ACTION_RESULT_HPP

#include "IEntity.hpp"
#include "StatusCode.hpp"
#include "Core/Memory.hpp"

#include <memory>

namespace Core {
class IActionResult : public IEntity {
  TYPE_INFO(IActionResult, IEntity, "result")

public:

  virtual ~IActionResult();

  virtual StatusCode getStatusCode() const = 0;
};

class RedirectResult : public IActionResult {
  TYPE_INFO(RedirectResult, IActionResult, "actionResult")

public:

  static RedirectResult::Unique ToRoute(String route);

  RedirectResult(String route) : route(route) {}

  virtual StatusCode getStatusCode() const override {
    return StatusCode::Redirect;
  }

  String getRoute() const {
    return route;
  }

private:

  const String route;
};

class StatusResult : public IActionResult {
  TYPE_INFO(StatusResult, IActionResult, "statusResult")

public:

  static StatusResult::Unique OK();
  static StatusResult::Unique Created(String message);
  static StatusResult::Unique Accepted();
  static StatusResult::Unique NoContent(String message);
  static StatusResult::Unique Conflict(String message);
  static StatusResult::Unique BadRequest(String message);
  static StatusResult::Unique BadRequest(String               message,
                                         StatusResult::Unique innerResult);
  static StatusResult::Unique NotFound(String message);
  static StatusResult::Unique InternalServerError(String message);
  static StatusResult::Unique InternalServerError(String               message,
                                                  StatusResult::Unique innerResult);
  static StatusResult::Unique NotImplemented();
  static StatusResult::Unique NotImplemented(String message);

  StatusResult(const StatusCode& statusCode) : statusCode(statusCode), message(
      statusCode.getText()) {}

  StatusResult(const StatusCode& statusCode, String message) : statusCode(
      statusCode), message(message) {}

  StatusResult(const StatusCode   & statusCode,
               String               message,
               StatusResult::Unique innerResult) : statusCode(statusCode),
    message(message),
    innerResult(std::move(innerResult)) {}

  // From IActionResult
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


class ObjectResult : public IActionResult {
  TYPE_INFO(ObjectResult, IActionResult, "objectResult")

public:

  static ObjectResult::Unique OK(IEntity::Unique entity) {
    return ObjectResult::makeUnique(
      StatusCode::OK,
      std::move(entity));
  }

  static ObjectResult::Unique Created(IEntity::Unique entity) {
    return ObjectResult::makeUnique(
      StatusCode::Created,
      std::move(entity));
  }

  ObjectResult(const StatusCode& statusCode, IEntity::Unique entity) :
    statusCode(statusCode), entity(std::move(entity)) {}

  // From IActionResult
  virtual StatusCode getStatusCode() const override {
    return statusCode;
  }

  const IEntity& getObject() const {
    return *entity;
  }

private:

  const StatusCode statusCode;
  const IEntity::Unique entity;
};
}

#endif /* end of include guard: CORE_ACTION_RESULT_HPP */
