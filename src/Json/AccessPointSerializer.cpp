#include "AccessPointSerializer.hpp"

using namespace Core;
using namespace Json;
using namespace Models;

#define FIELD_WIFI_NETWORK    "wifi_network"

Core::StatusResult::Unique
AccessPointSerializer::serialize(
  const AccessPoint& accessPoint,
  ISerializationContext& context) const {

  auto result = context.setValue(FIELD_WIFI_NETWORK, accessPoint.getNetworkSsid());
  if (!result->isOk())
    return result;

  return StatusResult::OK();
}

Core::StatusResult::Unique
AccessPointSerializer::deserialize(
  Models::AccessPoint::Unique& accessPoint,
  ISerializationContext& context) const {

  std::string networkSsid;
  auto result = context.getStringValue(FIELD_WIFI_NETWORK, networkSsid);
  if (!result->isOk())
    return result;

  accessPoint = AccessPoint::makeUnique(networkSsid);
  return StatusResult::OK();
}
