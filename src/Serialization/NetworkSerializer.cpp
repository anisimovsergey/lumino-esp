#include "NetworkSerializer.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Serialization;
using namespace Models;

#define FIELD_SSID "ssid"
#define FIELD_RSSI "rssi"
#define FIELD_ENCRYPTION "encryption"

Core::Status
NetworkSerializer::serializeImpl(
  ISerializationContext& context,
  const Network& network) const {

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

std::tuple<Core::Status, std::unique_ptr<Models::Network>>
NetworkSerializer::deserializeImpl(const IDeserializationContext& context) const {
  return std::make_tuple(Status::NotImplemented, nullptr);
}
