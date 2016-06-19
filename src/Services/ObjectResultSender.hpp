// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_OBJECT_RESULT_SENDER_HPP
#define SERVICES_OBJECT_RESULT_SENDER_HPP

#include "HttpSender.hpp"
#include "Json/ISerializationService.hpp"
#include "Core/ActionResult.hpp"

#include <memory>

namespace Services {

  class ObjectResultSender : public HttpSender<Core::ObjectResult> {
    public:
      ObjectResultSender(
        std::shared_ptr<const Json::ISerializationService> serializationService);

    protected:
      virtual std::shared_ptr<IHttpResponse> prepareResponse(
        IHttpRequest& request,
        const Core::ObjectResult& objectResult) const override;

    private:
      std::shared_ptr<const Json::ISerializationService>  serializationService;
  };

}

#endif /* end of include guard: SERVICES_OBJECT_RESULT_SENDER_HPP */
