// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_NETWORKS_SCAN_SERIALIZER_H
#define JSON_NETWORKS_SCAN_SERIALIZER_H

#include "Models/NetworksScan.hpp"
#include "Serializer.hpp"

namespace Json {

class NetworksScanSerializer : public Serializer<Models::NetworksScan> {
  public:
    String getTypeId() const override {
      return Models::NetworksScan::getStaticTypeId();
    }

  protected:
    Core::Status serialize(
      const Models::NetworksScan& scan,
      ISerializationContext& context) const override;

    Core::Status deserialize(
      std::shared_ptr<Models::NetworksScan>& scan,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_NETWORKS_SCAN_SERIALIZER_H */
