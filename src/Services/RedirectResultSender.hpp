// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_REDIRECT_RESULT_SENDER_HPP
#define SERVICES_REDIRECT_RESULT_SENDER_HPP

#include "HttpSender.hpp"
#include "Core/ActionResult.hpp"

namespace Services {

 class RedirectResultSender : public HttpSender<Core::RedirectResult> {
   protected:
     virtual std::shared_ptr<IHttpResponse> prepareResponse(
       const Json::ISerializationService& serializationSerivce,
       IHttpRequest& request,
       const Core::RedirectResult& redirectResult) const override;
  };

}

#endif /* end of include guard: SERVICES_REDIRECT_RESULT_SENDER_HPP */
