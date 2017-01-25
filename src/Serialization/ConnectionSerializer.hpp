// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERIALIZATION_CONNECTION_SERIALIZER_HPP
#define SERIALIZATION_CONNECTION_SERIALIZER_HPP

#include "Serialization/Serializer.hpp"
#include "Models/Connection.hpp"

namespace Serialization {

class ConnectionSerializer : public Serializer<Models::Connection> {
  TYPE_PTRS(ConnectionSerializer)
  protected:
    // From Serializer
    virtual Core::Status serialize(
      const Models::Connection& connection,
      ISerializationContext& context) const override;

    virtual Core::Status deserialize(
      Models::Connection::Unique& connection,
      IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_CONNECTION_SERIALIZER_HPP */
