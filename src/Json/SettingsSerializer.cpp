#include "SettingsSerializer.hpp"

using namespace Core;
using namespace Json;
using namespace Models;

std::unique_ptr<Core::StatusResult>
SettingsSerializer::serialize(const Settings& settings, ISerializationContext& context) const {
  context.setValue("name", settings.getDeviceName());
  return StatusResult::OK();
}

std::unique_ptr<Core::StatusResult>
SettingsSerializer::deserialize(
  std::unique_ptr<Models::Settings>& settings,
  ISerializationContext& context) const {

  String deviceName;
  auto actionResult = context.getStringValue("name", deviceName);
  if (!actionResult->isOk())
    return actionResult;

  settings = make_unique<Models::Settings>(deviceName);
  return StatusResult::OK();
}
