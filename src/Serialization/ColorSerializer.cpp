#include "ColorSerializer.hpp"

#include "Core/Memory.hpp"

using namespace Core;
using namespace Serialization;
using namespace Models;

#define FIELD_RED     "r"
#define FIELD_GREEN   "g"
#define FIELD_BLUE    "b"

Core::Status
ColorSerializer::serializeImpl(
  ISerializationContext& context,
  const Color& color) const {

  auto result = context.setInt(FIELD_RED, color.getR());
  if (!result.isOk())
    return result;

  result = context.setInt(FIELD_GREEN, color.getG());
  if (!result.isOk())
    return result;

  result = context.setInt(FIELD_BLUE, color.getB());
  if (!result.isOk())
    return result;

  return Status::OK;
}

std::tuple<Core::Status, std::unique_ptr<Models::Color>>
ColorSerializer::deserializeImpl(
  const IDeserializationContext& context) const {
  Status result;
  int r, g, b;
  std::tie(result, r) = context.getInt(FIELD_RED);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  std::tie(result, g) = context.getInt(FIELD_GREEN);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  std::tie(result, b) = context.getInt(FIELD_BLUE);
  if (!result.isOk())
    return std::make_tuple(result, nullptr);

  auto color = std::make_unique<Color>(r, g, b);
  return std::make_tuple(Status::OK, std::move(color));
}
