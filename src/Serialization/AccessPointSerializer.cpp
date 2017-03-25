#include "AccessPointSerializer.hpp"

#include "Core/Memory.hpp"

using namespace Core;
using namespace Serialization;
using namespace Models;

#define FIELD_WIFI_NETWORK "wifi_network"

Core::Status
AccessPointSerializer::serializeImpl(
  ISerializationContext& context,
  const AccessPoint& accessPoint) const {

  auto result = context.setString(FIELD_WIFI_NETWORK, accessPoint.getNetworkSsid());
  if (!result.isOk())
    return result;

  return Status::OK;
}

std::tuple<Core::Status, std::unique_ptr<Models::AccessPoint>>
AccessPointSerializer::deserializeImpl(const IDeserializationContext& context) const {
  Status result;
  std::string networkSsid;
  std::tie(result, networkSsid) = context.getString(FIELD_WIFI_NETWORK);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  auto accessPoint = std::make_unique<AccessPoint>(networkSsid);
  return std::make_tuple(Status::OK, std::move(accessPoint));
}
