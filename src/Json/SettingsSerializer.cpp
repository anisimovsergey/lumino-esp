#include "SettingsSerializer.hpp"

using namespace Core;
using namespace Json;
using namespace Models;

std::shared_ptr<Core::IActionResult>
SettingsSerializer::serialize(const Settings& settings, ISerializationContext& context) const {
  context.setValue("name", settings.getDeviceName());
  return StatusResult::OK();
}

std::shared_ptr<Core::IActionResult>
SettingsSerializer::deserialize(
  std::shared_ptr<Models::Settings>& settings,
  ISerializationContext& context) const {

  String deviceName;
  auto actionResult = context.getStringValue("name", deviceName);
  if (!actionResult->isOk())
    return actionResult;

  settings = std::shared_ptr<Models::Settings>(new Settings(deviceName));
  return StatusResult::OK();
}
