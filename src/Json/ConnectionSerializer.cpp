#include "ConnectionSerializer.hpp"

using namespace Core;
using namespace Json;
using namespace Models;

std::unique_ptr<Core::StatusResult>
ConnectionSerializer::serialize(
  const Connection& connection,
  ISerializationContext& context) const {

  context.setValue("wifi_network", connection.getNetworkSsid());
  context.setValue("connected", connection.getIsConnected());
  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
ConnectionSerializer::deserialize(
  std::unique_ptr<Models::Connection>& connection,
  ISerializationContext& context) const {

  String networkSsid;
  auto actionResult = context.getStringValue("wifi_network", networkSsid);
  if (!actionResult->isOk()) {
    return StatusResult::BadRequest(
      "Unable to deserialize type """ + getTypeId() + """.",
      std::move(actionResult));
  }

  String networkPassword;
  actionResult = context.getStringValue("wifi_password", networkPassword);
  if (!actionResult->isOk()) {
    return StatusResult::BadRequest(
      "Unable to deserialize type """ + getTypeId() + """.",
      std::move(actionResult));
  }

  connection = make_unique<Connection>(
    networkSsid, networkPassword
  );
  return StatusResult::OK();
}
