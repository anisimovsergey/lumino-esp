// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_STATUS_RESULT_SENDER_HPP
#define SERVICES_STATUS_RESULT_SENDER_HPP

#include "HttpSender.hpp"
#include "Json/ISerializationService.hpp"
#include "Core/ActionResult.hpp"

#include <memory>

namespace Services {

  class StatusResultSender : public HttpSender<Core::StatusResult> {
    public:
      StatusResultSender(
        std::shared_ptr<const Json::ISerializationService>  serializationService);

   protected:
     virtual std::unique_ptr<IHttpResponse> prepareResponse(
       IHttpRequest& request,
       const Core::StatusResult& statusResult) const override;

   private:
     std::shared_ptr<const Json::ISerializationService>  serializationService;
  };

}

#endif /* end of include guard: SERVICES_STATUS_RESULT_SENDER_HPP */
