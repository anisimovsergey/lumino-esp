#include "SettingsSerializer.hpp"

#include "Core/Memory.hpp"

using namespace Core;
using namespace Serialization;
using namespace Models;

#define FIELD_NAME "name"

Core::Status
SettingsSerializer::serializeImpl(ISerializationContext& context, const Settings& settings) const {
  auto result = context.setString(FIELD_NAME, settings.getDeviceName());
  if (!result.isOk())
    return result;

  return Status::OK;
}

std::tuple<Core::Status, std::unique_ptr<Settings>>
SettingsSerializer::deserializeImpl(
  const IDeserializationContext& context) const {
  Status result;
  std::string deviceName;
  std::tie(result, deviceName) = context.getString(FIELD_NAME);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  auto settings = std::make_unique<Settings>(deviceName);
  return std::make_tuple(Status::OK, std::move(settings));
}
