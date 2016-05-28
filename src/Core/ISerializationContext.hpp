// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_I_SERIALIZATION_CONTEXT_H
#define CORE_I_SERIALIZATION_CONTEXT_H

#include "ISerializable.hpp"

#include <WString.h>

namespace Core {

class ISerializationContext;

class IArraySerializationContext {
  public:
    virtual ISerializationContext& add(const ISerializable& element) = 0;
};

class ISerializationContext {
  public:
      virtual ~ISerializationContext() {};

      virtual String  getString(String key) const = 0;
      virtual bool    getBool(String key) const = 0;

      virtual void    setType(String type) = 0;
      virtual void    setValue(String key, String value) = 0;
      virtual void    setValue(String key, float value) = 0;
      virtual IArraySerializationContext& createArray(String key) = 0;
};

}

#endif /* end of include guard: CORE_I_SERIALIZATION_CONTEXT_H */
