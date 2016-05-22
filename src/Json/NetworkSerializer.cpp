#include "NetworkSerializer.hpp"
#include <ESP8266WiFi.h>
#include "ISerializationContext.hpp"

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

Network
NetworkSerializer::deserialie(const ISerializationContext& context) {
}

void
NetworkSerializer::serialie(const Network& network, ISerializationContext& context) {

  context.setType("network");
  context.setValue("ssid", network.getSsid());
  context.setValue("rssi", network.getRssi());
  context.setValue("encryption", getEncryptionTypeString(network.getEncryptionType()));
}
