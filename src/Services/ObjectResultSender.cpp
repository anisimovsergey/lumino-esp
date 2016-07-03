#include "ObjectResultSender.hpp"

using namespace Core;
using namespace Json;
using namespace Services;

ObjectResultSender::ObjectResultSender(
  std::shared_ptr<const ISerializationService> serializationService) :
  serializationService(serializationService) {
}

std::unique_ptr<Core::StatusResult>
ObjectResultSender::getResponse(
  IHttpRequest& request,
  const ObjectResult& objectResult,
  std::unique_ptr<IHttpResponse>& response) const {

  String json;
  int    code = objectResult.getStatusCode().getCode();
  auto status = serializationService->serialize(objectResult.getEntity(), json);
  if (!status->isOk())
    return status;

  response = request.createResponse(code, "text/json", json);
  return StatusResult::OK();
}
