#include "NetworkSerializer.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Serialization;
using namespace Models;

#define FIELD_SSID "ssid"
#define FIELD_RSSI "rssi"
#define FIELD_ENCRYPTION "encryption"

Core::Status
NetworkSerializer::serialize(
  const Network& network,
  ISerializationContext& context) const {

  auto result = context.setString(FIELD_SSID, network.getSsid());
  if (!result.isOk())
    return result;

  result = context.setInt(FIELD_RSSI, network.getRssi());
  if (!result.isOk())
    return result;

  result = context.setString(FIELD_ENCRYPTION, network.getEncryption());
  if (!result.isOk())
    return result;

  return Status::OK;
}

Core::Status
NetworkSerializer::deserialize(
  Models::Network::Unique& network,
  IDeserializationContext& context) const {

  return Status::NotImplemented;
}
