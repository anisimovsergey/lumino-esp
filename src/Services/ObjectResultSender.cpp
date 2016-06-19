#include "ObjectResultSender.hpp"

#include "Core/Logger.hpp"

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
  if (objectResult.getEntity()) {
    auto status = serializationService->serialize(*objectResult.getEntity(), json);
    if (!status->isOk()) {
      code = status->getStatusCode().getCode();
    }
  } else {
    Logger::error("Entity is empty.");
  }
  return request.createResponse(code, "text/json", json);
}
