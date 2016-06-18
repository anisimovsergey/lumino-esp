#include "SettingsSerializer.hpp"

using namespace Core;
using namespace Json;
using namespace Models;

std::shared_ptr<Core::ActionResult>
SettingsSerializer::serialize(const Settings& settings, ISerializationContext& context) const {
  context.setValue("name", settings.getDeviceName());
  return ActionResult::Success();
}

std::shared_ptr<Core::ActionResult>
SettingsSerializer::deserialize(
  std::shared_ptr<Models::Settings>& settings,
  ISerializationContext& context) const {

  String deviceName;
  auto actionResult = context.getStringValue("name", deviceName);
  if (!actionResult->isOk())
    return actionResult;

  settings = std::shared_ptr<Models::Settings>(new Settings(deviceName));
  return ActionResult::Success();
}
