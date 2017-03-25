#include "ConnectionSerializer.hpp"

#include "Core/Memory.hpp"

using namespace Core;
using namespace Serialization;
using namespace Models;

#define FIELD_WIFI_NETWORK    "wifi_network"
#define FIELD_WIFI_PASSWORD   "wifi_password"
#define FIELD_CONNECTED       "connected"

Core::Status
ConnectionSerializer::serializeImpl(
  ISerializationContext& context,
  const Connection& connection) const {

  auto result = context.setString(FIELD_WIFI_NETWORK, connection.getNetworkSsid());
  if (!result.isOk())
    return result;

  result = context.setBool(FIELD_CONNECTED, connection.getIsConnected());
  if (!result.isOk())
    return result;

  return Status::OK;
}

 std::tuple<Core::Status, std::unique_ptr<Models::Connection>>
ConnectionSerializer::deserializeImpl(
  const IDeserializationContext& context) const {
  Status result;
  std::string networkSsid;
  std::tie(result, networkSsid) = context.getString(FIELD_WIFI_NETWORK);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  std::string networkPassword;
  std::tie(result, networkPassword) = context.getString(FIELD_WIFI_PASSWORD);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  auto connection = std::make_unique<Connection>(networkSsid, networkPassword);
  return std::make_tuple(Status::OK, std::move(connection));
}
