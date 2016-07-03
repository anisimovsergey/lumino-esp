#include "RedirectResultSender.hpp"

using namespace Core;
using namespace Services;

std::unique_ptr<Core::StatusResult>
RedirectResultSender::getResponse(
  IHttpRequest& request,
  const RedirectResult& redirectResult,
  std::unique_ptr<IHttpResponse>& response) const {

  int  code = redirectResult.getStatusCode().getCode();
  response = request.createResponse(code);
  response->setHeader("Location", redirectResult.getRoute());

  return StatusResult::OK();
}
