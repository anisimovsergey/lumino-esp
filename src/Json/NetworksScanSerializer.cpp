#include "NetworksScanSerializer.hpp"

using namespace Core;
using namespace Json;
using namespace Models;

Status
NetworksScanSerializer::serialize(
  const NetworksScan& scan,
  ISerializationContext& context) const {

  context.setValue("status", scan.getStatus());
  context.setValue("networks", scan.getNetworks());

  return Status::Ok;
}

Status
NetworksScanSerializer::deserialize(
  std::shared_ptr<Models::NetworksScan>& scan,
  ISerializationContext& context) const {

  return Status::NotSupported;
}
