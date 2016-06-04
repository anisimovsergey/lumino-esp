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

  return Status::NotSupported;
}
