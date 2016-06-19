#include "StatusResultSender.hpp"

using namespace Core;
using namespace Json;
using namespace Services;

StatusResultSender::StatusResultSender(
  std::shared_ptr<const ISerializationService> serializationService) :
  serializationService(serializationService) {
}

std::shared_ptr<IHttpResponse>
StatusResultSender::prepareResponse(
  IHttpRequest& request,
  const StatusResult& statusResult) const {

  String json;
  int    code = statusResult.getStatusCode().getCode();
  auto status = serializationService->serialize(statusResult, json);
  if (!status->isOk()) {
    code = status->getStatusCode().getCode();
  }
  return request.createResponse(code, "text/json", json);
}
