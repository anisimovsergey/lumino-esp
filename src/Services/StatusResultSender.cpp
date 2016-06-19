#include "StatusResultSender.hpp"

using namespace Core;
using namespace Services;

std::shared_ptr<IHttpResponse>
StatusResultSender::prepareResponse(
  const Json::ISerializationService& serializationSerivce,
  IHttpRequest& request,
  const StatusResult& statusResult) const {

  String json;
  int    code = statusResult.getStatusCode().getCode();

  auto status = serializationSerivce.serialize(statusResult, json);
  if (!status->isOk()) {
    code = status->getStatusCode().getCode();
  }

  return request.createResponse(code, "text/json", json);
}
