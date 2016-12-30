#include "NetworkSerializer.hpp"

using namespace Core;
using namespace Json;
using namespace Models;

#define FIELD_SSID "ssid"
#define FIELD_RSSI "rssi"
#define FIELD_ENCRYPTION "encryption"

Core::StatusResult::Unique
NetworkSerializer::serialize(
  const Network& network,
  ISerializationContext& context) const {

  auto result = context.setValue(FIELD_SSID, network.getSsid());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_RSSI, network.getRssi());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_ENCRYPTION, network.getEncryption());
  if (!result->isOk())
    return result;

  return StatusResult::OK();
}

Core::StatusResult::Unique
NetworkSerializer::deserialize(
  Models::Network::Unique& network,
  ISerializationContext& context) const {

  return StatusResult::NotImplemented();
}
