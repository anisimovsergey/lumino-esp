#include "StatusSerializer.hpp"

using namespace Json;
using namespace Core;

Core::Status
StatusSerializer::serialize(const Status& status,
                            ISerializationContext& context) const {

  context.setValue("code", status.getCode());
  context.setValue("title", status.getTitle());
  return Status::Ok;
}

Core::Status
StatusSerializer::deserialize(
  std::shared_ptr<Core::Status>& status,
  ISerializationContext& context) const {

  return Status::NotSupported;
}
