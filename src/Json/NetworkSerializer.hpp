// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_NETWORK_SERIALIZER_H
#define JSON_NETWORK_SERIALIZER_H

#include "Core/Serializer.hpp"
#include "Models/Network.hpp"

namespace Json {

class NetworkSerializer : public Core::Serializer<Models::Network> {
  public:
    Models::Network deserialize(const Core::ISerializationContext& context);

  protected:
    void serialize(const Models::Network& network,
                  Core::ISerializationContext& context) override;
};

}

#endif /* end of include guard: JSON_NETWORK_SERIALIZER_H */
