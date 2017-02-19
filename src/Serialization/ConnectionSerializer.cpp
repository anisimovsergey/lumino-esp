#include "ConnectionSerializer.hpp"

#include "Core/Memory.hpp"

using namespace Core;
using namespace Serialization;
using namespace Models;

#define FIELD_WIFI_NETWORK    "wifi_network"
#define FIELD_WIFI_PASSWORD   "wifi_password"
#define FIELD_CONNECTED       "connected"

Core::Status
ConnectionSerializer::serialize(
  const Connection& connection,
  ISerializationContext& context) const {

  auto result = context.setString(FIELD_WIFI_NETWORK, connection.getNetworkSsid());
  if (!result.isOk())
    return result;

  result = context.setBool(FIELD_CONNECTED, connection.getIsConnected());
  if (!result.isOk())
    return result;

  return Status::OK;
}

Core::Status
ConnectionSerializer::deserialize(
  std::unique_ptr<Models::Connection>& connection,
  IDeserializationContext& context) const {

  std::string networkSsid;
  auto result = context.getString(FIELD_WIFI_NETWORK, networkSsid);
  if (!result.isOk())
    return result;

  std::string networkPassword;
  result = context.getString(FIELD_WIFI_PASSWORD, networkPassword);
  if (!result.isOk())
    return result;

  connection = std::make_unique<Connection>(networkSsid, networkPassword);
  return Status::OK;
}
