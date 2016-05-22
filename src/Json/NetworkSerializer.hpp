// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef NETWORKSERIALIZER_H
#define NETWORKSERIALIZER_H

#include <WString.h>
#include "../Models/Network.hpp"

class ISerializationContext;

class NetworkSerializer {
public:
  Network deserialie(const ISerializationContext& context);
  void serialie(const Network& network, ISerializationContext& context);
};

#endif /* end of include guard: NETWORKSERIALIZER_H */
