#include "ColorSerializer.hpp"

#include "Core/Memory.hpp"

using namespace Core;
using namespace Serialization;
using namespace Models;

#define FIELD_RED     "h"
#define FIELD_GREEN   "s"
#define FIELD_BLUE    "l"

Core::Status
ColorSerializer::serializeImpl(
  ISerializationContext& context,
  const Color& color) const {

  auto result = context.setFloat(FIELD_RED, color.getH());
  if (!result.isOk())
    return result;

  result = context.setFloat(FIELD_GREEN, color.getS());
  if (!result.isOk())
    return result;

  result = context.setFloat(FIELD_BLUE, color.getL());
  if (!result.isOk())
    return result;

  return Status::OK;
}

std::tuple<Core::Status, std::unique_ptr<Models::Color>>
ColorSerializer::deserializeImpl(
  const IDeserializationContext& context) const {
  Status result;
  float h, s, l;
  std::tie(result, h) = context.getFloat(FIELD_RED);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  std::tie(result, s) = context.getFloat(FIELD_GREEN);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  std::tie(result, l) = context.getFloat(FIELD_BLUE);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  auto color = std::make_unique<Color>(h, s, l);
  return std::make_tuple(Status::OK, std::move(color));
}
