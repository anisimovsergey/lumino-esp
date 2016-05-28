// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include "ISerializationContext.hpp"

namespace Json {

template <class T> class Serializer {
  public:
    T deserialie(const ISerializationContext& context);
    void serialie(ISerializationContext& context);
};

}

#endif /* end of include guard: JSON_SERIALIZER_H */
