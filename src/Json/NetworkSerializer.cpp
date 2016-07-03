#include "NetworkSerializer.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Json;
using namespace Models;

#define FIELD_SSID "ssid"
#define FIELD_RSSI "rssi"
#define FIELD_ENCRYPTION "encryption"

namespace {

String getEncryptionTypeString(int thisType) {
  switch (thisType) {
    case ENC_TYPE_WEP:
      return "WEP";
    case ENC_TYPE_TKIP:
      return "WPA";
    case ENC_TYPE_CCMP:
      return "WPA2";
    case ENC_TYPE_NONE:
      return "None";
    case ENC_TYPE_AUTO:
      return "Auto";
  }
  return "Unknown";
}

}

std::unique_ptr<Core::StatusResult>
NetworkSerializer::serialize(
  const Network& network,
  ISerializationContext& context) const {

  auto result = context.setValue(FIELD_SSID, network.getSsid());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_RSSI, network.getRssi());
  if (!result->isOk())
    return result;

  auto encryption = getEncryptionTypeString(network.getEncryptionType());
  result = context.setValue(FIELD_ENCRYPTION, encryption);
  if (!result->isOk())
    return result;

  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
NetworkSerializer::deserialize(
  std::unique_ptr<Models::Network>& network,
  ISerializationContext& context) const {

  return StatusResult::NotImplemented();
}
