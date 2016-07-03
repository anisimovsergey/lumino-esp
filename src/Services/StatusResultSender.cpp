#include "StatusResultSender.hpp"

using namespace Core;
using namespace Json;
using namespace Services;

StatusResultSender::StatusResultSender(
  std::shared_ptr<const ISerializationService> serializationService) :
  serializationService(serializationService) {
}

std::unique_ptr<Core::StatusResult>
StatusResultSender::getResponse(
  IHttpRequest& request,
  const StatusResult& statusResult,
  std::unique_ptr<IHttpResponse>& response) const {

  String json;
  int    code = statusResult.getStatusCode().getCode();
  auto status = serializationService->serialize(statusResult, json);
  if (!status->isOk())
    return status;

  response = request.createResponse(code, "text/json", json);
  return StatusResult::OK();
}
