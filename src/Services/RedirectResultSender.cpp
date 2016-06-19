#include "RedirectResultSender.hpp"

using namespace Core;
using namespace Services;

std::shared_ptr<IHttpResponse>
RedirectResultSender::prepareResponse(
  const Json::ISerializationService& serializationSerivce,
  IHttpRequest& request,
  const RedirectResult& redirectResult) const {

  String json;
  int  code = redirectResult.getStatusCode().getCode();
  auto response = request.createResponse(code);
  response->setHeader("Location", redirectResult.getRoute());
}
