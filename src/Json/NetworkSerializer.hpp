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
    String getTypeId() const override {
      return Models::Network::getStaticTypeId();
    }

  protected:
    std::unique_ptr<Core::IActionResult> serialize(
      const Models::Network& network,
      ISerializationContext& context) const override;

    std::unique_ptr<Core::IActionResult> deserialize(
      std::shared_ptr<Models::Network>& network,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_NETWORK_SERIALIZER_HPP */
