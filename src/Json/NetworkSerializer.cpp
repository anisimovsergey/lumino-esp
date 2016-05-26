#include "NetworkSerializer.hpp"
#include "ISerializationContext.hpp"
#include "Models/Network.hpp"

#include <ESP8266WiFi.h>

using namespace Json;
using namespace Models;

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

Models::Network
NetworkSerializer::deserialie(const Json::ISerializationContext& context) {
}

void
NetworkSerializer::serialie(const Models::Network& network,
  Json::ISerializationContext& context) {

  context.setType("network");
  context.setValue("ssid", network.getSsid());
  context.setValue("rssi", network.getRssi());

  String encryption = getEncryptionTypeString(network.getEncryptionType());
  context.setValue("encryption", encryption);
}
