// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_CONNECTION_SERIALIZER_HPP
#define JSON_CONNECTION_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Models/Connection.hpp"

namespace Json {

class ConnectionSerializer : public Serializer<Models::Connection> {
  TYPE_PTRS(ConnectionSerializer)
  protected:
    // From Serializer
    virtual Core::StatusResult::Unique serialize(
      const Models::Connection& connection,
      ISerializationContext& context) const override;

    virtual Core::StatusResult::Unique deserialize(
      Models::Connection::Unique& connection,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_CONNECTION_SERIALIZER_HPP */
