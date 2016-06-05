#include "ConnectionSerializer.hpp"

#include "Core/Status.hpp"

using namespace Core;
using namespace Json;
using namespace Models;

Core::Status
ConnectionSerializer::serialize(
  const Connection& connection,
  ISerializationContext& context) const {

  context.setValue("wifi_network", connection.getNetworkSsid());
  context.setValue("connected", connection.getIsConnected());
  return Status::Ok;
}

Core::Status
ConnectionSerializer::deserialize(
  std::shared_ptr<Models::Connection>& connection,
  ISerializationContext& context) const {

  String networkSsid;
  Status status = context.getStringValue("wifi_network", networkSsid);
  if (!status.isOk())
    return status;

  String networkPassword;
  status = context.getStringValue("wifi_password", networkPassword);
  if (!status.isOk())
    return status;

  connection = std::shared_ptr<Models::Connection>(
    new Connection(networkSsid, networkPassword));
  return Status::Ok;
}
