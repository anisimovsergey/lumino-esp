// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_SERIALIZER_H
#define CORE_SERIALIZER_H

#include "ISerializer.hpp"

namespace Core {

template <class T> class Serializer : public ISerializer {
  public:
    virtual void serialize(const ISerializable& object,
                           ISerializationContext& context) override {
        context.setType(object.getTypeId());
        const T& objectT = static_cast<const T&>(object);
        serialize(objectT, context);
    }

  protected:
    virtual void serialize(const T& object,
                           ISerializationContext& context) = 0;
 };

}

#endif /* end of include guard: CORE_SERIALIZER_H */
