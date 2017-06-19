#include "ConnectionSerializer.hpp"

#include "Core/Memory.hpp"
#include "Core/Format.hpp"

using namespace Core;
using namespace Serialization;
using namespace Models;

#define FIELD_SSID                "ssid"
#define FIELD_PASSWORD            "password"
#define FIELD_IS_CONNECTED        "isConnected"
#define FIELD_IS_PROTECTED        "isProtected"
#define FIELD_RSSI                "rssi"
#define FIELD_LOCAL_IP            "localIP"
#define FIELD_SUBNET_MASK         "subnetMask"
#define FIELD_GATEWAY_IP          "gatewayIP"
#define FIELD_DNS_IP              "dnsIP"
#define FIELD_DISCONNECT_REASON   "disconnectReason"

Core::Status
ConnectionSerializer::serializeImpl(
  ISerializationContext& context,
  const Connection& connection) const {

  auto result = context.setString(FIELD_SSID, connection.getSsid());
  if (!result.isOk())
    return result;

  result = context.setBool(FIELD_IS_CONNECTED, connection.getIsConnected());
  if (!result.isOk())
    return result;

  result = context.setBool(FIELD_IS_PROTECTED, connection.getIsProtected());
  if (!result.isOk())
    return result;

  result = context.setInt(FIELD_RSSI, connection.getRssi());
  if (!result.isOk())
    return result;

  result = context.setString(FIELD_LOCAL_IP, Core::ipToString(connection.getLocalIP()));
  if (!result.isOk())
    return result;

  result = context.setString(FIELD_SUBNET_MASK, Core::ipToString(connection.getSubnetMask()));
  if (!result.isOk())
    return result;

  result = context.setString(FIELD_GATEWAY_IP, Core::ipToString(connection.getGatewayIP()));
  if (!result.isOk())
    return result;

  result = context.setString(FIELD_DNS_IP, Core::ipToString(connection.getDnsIP()));
  if (!result.isOk())
    return result;

  result = context.setInt(FIELD_DISCONNECT_REASON, connection.getDisconnectReason());
  if (!result.isOk())
    return result;

  return Status::OK;
}

std::tuple<Core::Status, std::unique_ptr<Models::Connection>>
ConnectionSerializer::deserializeImpl(
  const IDeserializationContext& context) const {
  Status result;
  std::string ssid;
  std::tie(result, ssid) = context.getString(FIELD_SSID);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  std::string password;
  std::tie(result, password) = context.getString(FIELD_PASSWORD);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  auto connection = std::make_unique<Connection>(ssid, password);
  return std::make_tuple(Status::OK, std::move(connection));
}
