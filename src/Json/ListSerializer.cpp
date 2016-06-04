#include "ListSerializer.hpp"

#include "Models/Network.hpp"

using namespace Json;
using namespace Core;

Status
ListSerializer::serialize(
  const IList& list,
  ISerializationContext& context) const {

  context.setValue("elements", list);
  return Status::Ok;
}

Status
ListSerializer::deserialize(
  std::shared_ptr<IList>& list,
  ISerializationContext& context) const {

  List<Models::Network> networks;
  auto st = List<Models::Network>::dynamicCast(*list, networks);

  return Status::NotSupported;
}
