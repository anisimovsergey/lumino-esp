// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_OBJECT_RESULT_SENDER_HPP
#define JSON_OBJECT_RESULT_SENDER_HPP

#include "HttpSender.hpp"
#include "Core/ActionResult.hpp"

namespace Services {

 class ObjectResultSender : public HttpSender<Core::ObjectResult> {
   protected:
     virtual std::shared_ptr<IHttpResponse> prepareResponse(
       const Json::ISerializationService& serializationSerivce,
       IHttpRequest& request,
       const Core::ObjectResult& objectResult) const override;
  };

}

#endif /* end of include guard: JSON_OBJECT_RESULT_SENDER_HPP */
