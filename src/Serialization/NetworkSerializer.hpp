// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERIALIZATION_NETWORK_SERIALIZER_HPP
#define SERIALIZATION_NETWORK_SERIALIZER_HPP

#include "Serialization/Serializer.hpp"
#include "Models/Network.hpp"

namespace Serialization {

class NetworkSerializer : public Serializer<Models::Network> {
  TYPE_PTRS(NetworkSerializer)
  protected:
    // From Serializer
    virtual Core::Status serialize(
      const Models::Network& network,
      ISerializationContext& context) const override;

    virtual Core::Status deserialize(
      Models::Network::Unique& network,
      IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_NETWORK_SERIALIZER_HPP */
