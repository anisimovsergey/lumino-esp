#include "ObjectResultSender.hpp"

using namespace Core;
using namespace Services;

std::shared_ptr<IHttpResponse>
ObjectResultSender::prepareResponse(
  const Json::ISerializationService& serializationSerivce,
  IHttpRequest& request,
  const ObjectResult& objectResult) const {

  String json;
  int    code = objectResult.getStatusCode().getCode();
  auto status = serializationSerivce.serialize(*objectResult.getEntity(), json);
  if (!status->isOk()) {
    code = status->getStatusCode().getCode();
  }
  return request.createResponse(code, "text/json", json);
}
