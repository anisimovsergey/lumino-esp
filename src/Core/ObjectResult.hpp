// Copyright Sergey Anisimov 2016-2017

// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_OBJECT_RESULT_HPP
#define CORE_OBJECT_RESULT_HPP

#include "ActionResult.hpp"

namespace Core {

class ObjectResult : public ActionResult {
  TYPE_INFO(ObjectResult, ActionResult, "objectResult")

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

  // From ActionResult
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

#endif /* end of include guard: CORE_OBJECT_RESULT_HPP */
