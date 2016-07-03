// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_ACTION_RESULT_HPP
#define CORE_ACTION_RESULT_HPP

#include "Entity.hpp"
#include "StatusCode.hpp"
#include "Core/Memory.hpp"

#include <memory>

namespace Core {

class IActionResult : public IEntity {
  public:
    virtual ~IActionResult() {};

    virtual StatusCode getStatusCode() const = 0;
};

template<class T>
class ActionResult : public IActionResult {
  public:
    // From IEntity
    virtual String getTypeId() const override {
      return T::getStaticTypeId();
    }
};

class RedirectResult : public ActionResult<RedirectResult> {
public:
  static String getStaticTypeId() { return "redirectResult"; }

  static std::unique_ptr<RedirectResult> ToRoute(String route);

  RedirectResult(String route) : route(route) {
  }

  virtual StatusCode getStatusCode() const override {
    return StatusCode::Redirect;
  }

  String getRoute() const {
    return route;
  }

private:
  const String route;
};

class StatusResult : public ActionResult<StatusResult> {
  public:
    static String  getStaticTypeId() { return "statusResult"; }

    static std::unique_ptr<StatusResult> OK();
    static std::unique_ptr<StatusResult> Conflict(String message);
    static std::unique_ptr<StatusResult> BadRequest(String message);
    static std::unique_ptr<StatusResult> BadRequest(String message,
      std::unique_ptr<StatusResult> innerResult);
    static std::unique_ptr<StatusResult> NotFound(String message);
    static std::unique_ptr<StatusResult> InternalServerError(String message);
    static std::unique_ptr<StatusResult> InternalServerError(String message,
      std::unique_ptr<StatusResult> innerResult);
    static std::unique_ptr<StatusResult> NotImplemented();
    static std::unique_ptr<StatusResult> NotImplemented(String message);

    StatusResult(const StatusCode& statusCode) :
      statusCode(statusCode), message(statusCode.getText()) {
    }
    StatusResult(const StatusCode& statusCode, String message) :
      statusCode(statusCode), message(message) {
    }
    StatusResult(const StatusCode& statusCode, String message,
      std::unique_ptr<StatusResult> innerResult) :
      statusCode(statusCode), message(message),
      innerResult(std::move(innerResult)) {
    }

    // From IActionResult
    virtual StatusCode getStatusCode() const override {
      return statusCode;
    }

    bool isOk() const {
      return (getStatusCode() == StatusCode::OK);
    }

    String getMessage() const {
      return message;
    }

    const StatusResult* getInnerReuslt() const {
      return innerResult.get();
    }

  private:
    const StatusCode statusCode;
    const String message;
    const std::unique_ptr<StatusResult> innerResult;
};


class ObjectResult : public ActionResult<ObjectResult> {
  public:
    static String  getStaticTypeId() { return "objectResult"; }

    static std::unique_ptr<ObjectResult> OK(std::unique_ptr<IEntity> entity) {
      return make_unique<ObjectResult>(
        StatusCode::OK,
        std::move(entity));
    }

    ObjectResult(const StatusCode& statusCode, std::unique_ptr<IEntity> entity) :
      statusCode(statusCode), entity(std::move(entity)) {
    }

    // From IActionResult
    virtual StatusCode getStatusCode() const override {
      return statusCode;
    }

    const IEntity& getEntity() const {
      return *entity;
    }

  private:
    const StatusCode statusCode;
    const std::unique_ptr<IEntity> entity;
};

}

#endif /* end of include guard: CORE_ACTION_RESULT_HPP */
