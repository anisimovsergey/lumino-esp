#include "NetworkSerializer.hpp"

#include <ESP8266WiFi.h>

using namespace Core;
using namespace Json;
using namespace Models;

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
}

}

Status
NetworkSerializer::serialize(
  const Network& network,
  ISerializationContext& context) const {

  context.setValue("ssid", network.getSsid());
  context.setValue("rssi", network.getRssi());

  String encryption = getEncryptionTypeString(network.getEncryptionType());
  context.setValue("encryption", encryption);

  return Status::Ok;
}

Status
NetworkSerializer::deserialize(
  std::shared_ptr<Models::Network>& network,
  ISerializationContext& context) const {

  return Status::NotSupported;
}
