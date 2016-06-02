#include "SettingsSerializer.hpp"

using namespace Json;
using namespace Models;

Settings
SettingsSerializer::deserialize(const ISerializationContext& context) {
  /*
  String deviceName = context.getString("name");
  String networkSsid = context.getString("wifi_network");
  String networkPassword = context.getString("wifi_password");
  Settings settings(deviceName, networkSsid, networkPassword);
  settings.setIsConnected(context.getBool("connected"));
  return settings;
  */
}

void
SettingsSerializer::serialize(const Settings& settings, ISerializationContext& context) const {
  context.setValue("name", settings.getDeviceName());
  context.setValue("wifi_network", settings.getNetworkSsid());
  context.setValue("connected", settings.getIsConnected());
}
