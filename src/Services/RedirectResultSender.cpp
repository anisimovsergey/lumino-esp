#include "RedirectResultSender.hpp"

#include "Core/Logger.hpp"

using namespace Core;
using namespace Services;

std::unique_ptr<IHttpResponse>
RedirectResultSender::prepareResponse(
  IHttpRequest& request,
  const RedirectResult& redirectResult) const {

  Logger::message("Getting code...");
  int  code = redirectResult.getStatusCode().getCode();
  Logger::message("Creating response...");
  auto response = request.createResponse(code);
  Logger::message("Setting location...");
  response->setHeader("Location", redirectResult.getRoute());
  Logger::message("Returning response...");
  return response;
}
