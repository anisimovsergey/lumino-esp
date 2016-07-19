#include "ConnectionSerializer.hpp"

using namespace Core;
using namespace Json;
using namespace Models;

#define FIELD_WIFI_NETWORK    "wifi_network"
#define FIELD_WIFI_PASSWORD   "wifi_password"
#define FIELD_CONNECTED       "connected"

std::unique_ptr<Core::StatusResult>
ConnectionSerializer::serialize(
  const Connection& connection,
  ISerializationContext& context) const {

  auto result = context.setValue(FIELD_WIFI_NETWORK, connection.getNetworkSsid());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_CONNECTED, connection.getIsConnected());
  if (!result->isOk())
    return result;

  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
ConnectionSerializer::deserialize(
  std::unique_ptr<Models::Connection>& connection,
  ISerializationContext& context) const {

  String networkSsid;
  auto result = context.getStringValue(FIELD_WIFI_NETWORK, networkSsid);
  if (!result->isOk())
    return result;

  String networkPassword;
  result = context.getStringValue(FIELD_WIFI_PASSWORD, networkPassword);
  if (!result->isOk())
    return result;

  connection = Connection::makeUnique(networkSsid, networkPassword);
  return StatusResult::OK();
}
