#include "ConnectionSerializer.hpp"

using namespace Core;
using namespace Json;
using namespace Models;

std::unique_ptr<Core::IActionResult>
ConnectionSerializer::serialize(
  const Connection& connection,
  ISerializationContext& context) const {

  context.setValue("wifi_network", connection.getNetworkSsid());
  context.setValue("connected", connection.getIsConnected());
  return StatusResult::OK();
}

std::unique_ptr<Core::IActionResult>
ConnectionSerializer::deserialize(
  std::shared_ptr<Models::Connection>& connection,
  ISerializationContext& context) const {

  String networkSsid;
  auto actionResult = context.getStringValue("wifi_network", networkSsid);
  if (!actionResult->isOk())
    return actionResult;

  String networkPassword;
  actionResult = context.getStringValue("wifi_password", networkPassword);
  if (!actionResult->isOk())
    return actionResult;

  connection = std::make_shared<Models::Connection>(
    networkSsid, networkPassword);
  return StatusResult::OK();
}
