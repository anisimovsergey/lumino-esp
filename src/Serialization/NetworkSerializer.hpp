// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERIALIZATION_NETWORK_SERIALIZER_HPP
#define SERIALIZATION_NETWORK_SERIALIZER_HPP

#include "Serialization/Serializer.hpp"
#include "Models/Network.hpp"

#include <memory>

namespace Serialization {

class NetworkSerializer : public Serializer<Models::Network> {
  protected:
    virtual Core::Status serializeImpl(
      ISerializationContext& context,
      const Models::Network& network) const override;

    virtual std::tuple<Core::Status, std::unique_ptr<Models::Network>> deserializeImpl(
      const IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_NETWORK_SERIALIZER_HPP */
