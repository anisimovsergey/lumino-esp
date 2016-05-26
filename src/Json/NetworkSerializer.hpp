// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_NETWORK_SERIALIZER_H
#define JSON_NETWORK_SERIALIZER_H

#include "ISerializationContext.hpp"
#include "Models/Network.hpp"

namespace Json {

class NetworkSerializer {
  public:
    Models::Network deserialie(const ISerializationContext& context);
    void serialie(const Models::Network& network,
                  ISerializationContext& context);
};

}

#endif /* end of include guard: JSON_NETWORK_SERIALIZER_H */
