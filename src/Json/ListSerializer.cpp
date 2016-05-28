#include "ListSerializer.hpp"

using namespace Json;
using namespace Core;

/*
void onGetWiFiNetworks() {
  int networksCount = WiFi.scanNetworks();
  if (networksCount == -1) {
    server.sendError(Errors.UnableToScanFiFiNetworks);
  } else {
    String json = "[";
    for (int networkNum = 0; networkNum < networksCount; networkNum++) {
      json += "{";
      json += "\"ssid\": \"" + WiFi.SSID(networkNum) + "\",";
      json += "\"rssi\": " + String(WiFi.RSSI(networkNum)) + ",";
      json += "\"encryption\": \"" + getEncryptionType(WiFi.encryptionType(networkNum)) + "\"";
      json += "}";
      if (networkNum < networksCount - 1)
        json += ",";
    }
    json += "]";
    server.send(200, "text/json", json);
  }
}
*/

void
ListSerializer::serialize(const IList& list,
                          ISerializationContext& context) {
    auto& collection = context.createArray("elements");
    list.forEach([&](const ISerializable& element) {
      collection.add(element);
    });
}
