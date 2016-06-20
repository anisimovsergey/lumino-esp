// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_ACTION_RESULT_HPP
#define CORE_ACTION_RESULT_HPP

#include "Entity.hpp"
#include "StatusCode.hpp"

#include <memory>

namespace Core {

class IActionResult : public IEntity {
public:
  virtual ~IActionResult() {};

  virtual bool        isOk() const = 0;
  virtual StatusCode  getStatusCode() const = 0;
};

template<class T> class ActionResult : public IActionResult {
  public:
    // From IEntity
    virtual String getTypeId() const override {
      return T::getStaticTypeId();
    }

    // From IActionResult
    virtual bool        isOk() const override {
      return (statusCode == StatusCode::OK);
    }
    virtual StatusCode  getStatusCode() const override {
      return statusCode;
    }

  protected:
    ActionResult(const StatusCode& statusCode) : statusCode(statusCode) {
    }

  private:
    const StatusCode statusCode;
};

class StatusResult : public ActionResult<StatusResult> {
  public:
    static String  getStaticTypeId() { return "statusResult"; }

    static std::shared_ptr<IActionResult> OK();
    static std::shared_ptr<IActionResult> Conflict(String message);
    static std::shared_ptr<IActionResult> BadRequest(String message);
    static std::shared_ptr<IActionResult> NotFound(String message);
    static std::shared_ptr<IActionResult> InternalServerError(String message);
    static std::shared_ptr<IActionResult> NotImplemented();
    static std::shared_ptr<IActionResult> NotImplemented(String message);

    String getMessage() const { return message; }

  private:
    const String message;

    StatusResult(const StatusCode& statusCode) :
      ActionResult(statusCode), message(statusCode.getText()) {
    }
    StatusResult(const StatusCode& statusCode, String message) :
      ActionResult(statusCode), message(message) {
    }
};

class RedirectResult : public ActionResult<RedirectResult> {
public:
  static String  getStaticTypeId() { return "redirectResult"; }

  static std::shared_ptr<IActionResult> ToRoute(String route);

  String getRoute() const { return route; }

private:
  const String route;

  RedirectResult(String route) :
    ActionResult(StatusCode::Redirect), route(route) {
  }
};

class ObjectResult : public ActionResult<ObjectResult> {
  public:
    static String  getStaticTypeId() { return "objectResult"; }

    static std::shared_ptr<IActionResult> OK(
      std::shared_ptr<IEntity> entity);

    const std::shared_ptr<IEntity> getEntity() const { return entity; };

  private:
    const std::shared_ptr<IEntity> entity;

    ObjectResult(const std::shared_ptr<IEntity> entity) :
      ActionResult(StatusCode::OK), entity(entity) {
    }
};

}

#endif /* end of include guard: CORE_ACTION_RESULT_HPP */
