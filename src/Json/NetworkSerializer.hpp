// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_NETWORK_SERIALIZER_HPP
#define JSON_NETWORK_SERIALIZER_HPP

#include "Models/Network.hpp"
#include "Serializer.hpp"

namespace Json {

class NetworkSerializer : public Serializer<Models::Network> {
  TYPE_PTRS(NetworkSerializer)
  protected:
    // From Serializer
    virtual Core::StatusResult::Unique serialize(
      const Models::Network& network,
      ISerializationContext& context) const override;

    virtual Core::StatusResult::Unique deserialize(
      Models::Network::Unique& network,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_NETWORK_SERIALIZER_HPP */
