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
  static StatusResult::Unique NotImplemented();

  StatusResult(const StatusCode& statusCode, const std::string& message);

  StatusResult(const StatusCode& statusCode, const std::string& message,
               StatusResult::Unique innerResult);

  virtual StatusCode getStatusCode() const override {
    return statusCode;
  }

  bool isOk() const {
    return getStatusCode() == StatusCode::OK;
  }

  bool isAccepted() const {
    return getStatusCode() == StatusCode::Accepted;
  }

  std::string getMessage() const {
    return message;
  }

  const StatusResult* getInnerReuslt() const {
    return innerResult.get();
  }

private:
  const StatusCode            statusCode;
  const std::string           message;
  const StatusResult::Unique  innerResult;
};

}

#endif /* end of include guard: CORE_ACTION_RESULT_HPP */
