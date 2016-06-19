#include "ObjectResultSender.hpp"

using namespace Core;
using namespace Json;
using namespace Services;

ObjectResultSender::ObjectResultSender(
  std::shared_ptr<const ISerializationService> serializationService) :
  serializationService(serializationService) {
}

std::shared_ptr<IHttpResponse>
ObjectResultSender::prepareResponse(
  IHttpRequest& request,
  const ObjectResult& objectResult) const {

  String json;
  int    code = objectResult.getStatusCode().getCode();
  auto status = serializationService->serialize(*objectResult.getEntity(), json);
  if (!status->isOk()) {
    code = status->getStatusCode().getCode();
  }
  return request.createResponse(code, "text/json", json);
}
