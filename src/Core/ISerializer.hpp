// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_I_SERIALIZER_H
#define CORE_I_SERIALIZER_H

#include "ISerializable.hpp"
#include "ISerializationContext.hpp"

namespace Core {

class ISerializer {
  public:
    virtual ~ISerializer() {};
    virtual void serialize(const ISerializable& object,
                           ISerializationContext& context) = 0;
};

}

#endif /* end of include guard: CORE_I_SERIALIZER_H */
