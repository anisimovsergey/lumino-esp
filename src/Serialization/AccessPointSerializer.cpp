#include "AccessPointSerializer.hpp"

#include "Core/Memory.hpp"

using namespace Core;
using namespace Serialization;
using namespace Models;

#define FIELD_WIFI_NETWORK "wifi_network"

Core::Status
AccessPointSerializer::serialize(
  const AccessPoint& accessPoint,
  ISerializationContext& context) const {

  auto result = context.setString(FIELD_WIFI_NETWORK, accessPoint.getNetworkSsid());
  if (!result.isOk())
    return result;

  return Status::OK;
}

Core::Status
AccessPointSerializer::deserialize(
  std::unique_ptr<AccessPoint>& accessPoint,
  IDeserializationContext& context) const {

  std::string networkSsid;
  auto result = context.getString(FIELD_WIFI_NETWORK, networkSsid);
  if (!result.isOk())
    return result;

  accessPoint = std::make_unique<AccessPoint>(networkSsid);
  return Status::OK;
}
