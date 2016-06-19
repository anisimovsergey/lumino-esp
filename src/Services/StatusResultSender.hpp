// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_STATUS_RESULT_SENDER_HPP
#define JSON_STATUS_RESULT_SENDER_HPP

#include "HttpSender.hpp"
#include "Core/ActionResult.hpp"

namespace Services {

 class StatusResultSender : public HttpSender<Core::StatusResult> {
   protected:
     virtual std::shared_ptr<IHttpResponse> prepareResponse(
       const Json::ISerializationService& serializationSerivce,
       IHttpRequest& request,
       const Core::StatusResult& statusResult) const override;
  };

}

#endif /* end of include guard: JSON_STATUS_RESULT_SENDER_HPP */
