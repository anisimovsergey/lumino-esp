// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_NETWORKS_SERIALIZER_HPP
#define JSON_NETWORKS_SERIALIZER_HPP

#include "Models/Networks.hpp"
#include "Serializer.hpp"

namespace Json {

class NetworksSerializer : public Serializer<Models::Networks> {
  TYPE_PTRS(NetworksSerializer)
  protected:
    // From Serializer
    virtual Core::StatusResult::Unique serialize(
      const Models::Networks& networks,
      ISerializationContext& context) const override;

    virtual Core::StatusResult::Unique deserialize(
     Models::Networks::Unique& networks,
     ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_NETWORKS_SERIALIZER_HPP */
