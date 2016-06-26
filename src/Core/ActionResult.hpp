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

  virtual bool        isOk() const = 0;
  virtual StatusCode  getStatusCode() const = 0;
};

template<class T>
class ActionResult : public IActionResult {
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

    static std::unique_ptr<IActionResult> OK();
    static std::unique_ptr<IActionResult> Conflict(String message);
    static std::unique_ptr<IActionResult> BadRequest(String message);
    static std::unique_ptr<IActionResult> NotFound(String message);
    static std::unique_ptr<IActionResult> InternalServerError(String message);
    static std::unique_ptr<IActionResult> NotImplemented();
    static std::unique_ptr<IActionResult> NotImplemented(String message);

    StatusResult(const StatusCode& statusCode) :
      ActionResult(statusCode), message(statusCode.getText()) {
    }
    StatusResult(const StatusCode& statusCode, String message) :
      ActionResult(statusCode), message(message) {
    }

    String getMessage() const { return message; }

  private:
    const String message;
};

class RedirectResult : public ActionResult<RedirectResult> {
public:
  static String  getStaticTypeId() { return "redirectResult"; }

  static std::unique_ptr<IActionResult> ToRoute(String route);

  RedirectResult(String route) :
    ActionResult(StatusCode::Redirect), route(route) {
  }

  String getRoute() const { return route; }

private:
  const String route;
};

class ObjectResultBase : public ActionResult<ObjectResultBase> {
  public:
    static String  getStaticTypeId() { return "objectResult"; }

    virtual const IEntity& getEntity() const = 0;

  protected:
    ObjectResultBase(const StatusCode& statusCode) : ActionResult(statusCode) {
    }
};

template<class T>
class ObjectResult : public ObjectResultBase {
  public:
    static std::unique_ptr<ObjectResult<T>> OK(std::unique_ptr<T> entity) {
      return make_unique<ObjectResult>(
        StatusCode::OK,
        std::move(entity));
    }

    ObjectResult(const StatusCode& statusCode, std::unique_ptr<T> entity) :
      ObjectResultBase(statusCode), entity(std::move(entity)) {
    }

    const T& get() const {
      return *entity;
    }

    virtual const IEntity& getEntity() const override {
      return *entity;
    }

  private:
    std::unique_ptr<T> entity;
};

}

#endif /* end of include guard: CORE_ACTION_RESULT_HPP */
