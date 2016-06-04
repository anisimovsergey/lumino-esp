#include "SettingsSerializer.hpp"

#include "Core/Status.hpp"

using namespace Core;
using namespace Json;
using namespace Models;

Core::Status
SettingsSerializer::serialize(const Settings& settings, ISerializationContext& context) const {
  context.setValue("name", settings.getDeviceName());
  context.setValue("wifi_network", settings.getNetworkSsid());
  context.setValue("connected", settings.getIsConnected());
  return Status::Ok;
}

Core::Status
SettingsSerializer::deserialize(
  std::shared_ptr<Models::Settings>& settings,
  ISerializationContext& context) const {

  String deviceName;
  Status status = context.getStringValue("name", deviceName);
  if (!status.isOk())
    return status;

  String networkSsid;
  status = context.getStringValue("wifi_network", networkSsid);
  if (!status.isOk())
    return status;

  String networkPassword;
  status = context.getStringValue("wifi_password", networkPassword);
  if (!status.isOk())
    return status;

  bool connected;
  status = context.getBoolValue("connected", connected);
  if (!status.isOk())
    return status;

  settings = std::shared_ptr<Models::Settings>(
    new Settings(deviceName, networkSsid, networkPassword, connected));
  return Status::Ok;
}
