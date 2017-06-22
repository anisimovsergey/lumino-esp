// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Lumino
// https://github.com/anisimovsergey/lumino-esp

#ifndef SERIALIZATION_CONNECTION_SERIALIZER_HPP
#define SERIALIZATION_CONNECTION_SERIALIZER_HPP

#include "Serialization/Serializer.hpp"
#include "Models/Connection.hpp"

#include <memory>

namespace Serialization {

class ConnectionSerializer : public Serializer<Models::Connection> {
  protected:
    // From Serializer
    virtual Core::Status serializeImpl(
      ISerializationContext& context,
      const Models::Connection& connection) const override;

    virtual std::tuple<Core::Status, std::unique_ptr<Models::Connection>> deserializeImpl(
      const IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_CONNECTION_SERIALIZER_HPP */
