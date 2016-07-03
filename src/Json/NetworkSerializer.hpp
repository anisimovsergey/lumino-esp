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
  public:
    // From ISerializer
    virtual String getTypeId() const override {
      return Models::Network::getStaticTypeId();
    }

  protected:
    // From Serializer
    virtual std::unique_ptr<Core::StatusResult> serialize(
      const Models::Network& network,
      ISerializationContext& context) const override;

    virtual std::unique_ptr<Core::StatusResult> deserialize(
      std::unique_ptr<Models::Network>& network,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_NETWORK_SERIALIZER_HPP */
