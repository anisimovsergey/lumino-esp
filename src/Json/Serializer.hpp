// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include "ISerializer.hpp"

namespace Json {

template <class T> class Serializer : public ISerializer {
  public:
    virtual void serialize(const Core::IEntity& object,
                           ISerializationContext& context) const override {
        context.setValue("type", object.getTypeId());
        const T& objectT = static_cast<const T&>(object);
        serialize(objectT, context);
    }

  protected:
    virtual void serialize(const T& object,
                           ISerializationContext& context) const = 0;
 };

}

#endif /* end of include guard: JSON_SERIALIZER_H */
