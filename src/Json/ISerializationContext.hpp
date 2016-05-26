// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_I_SERIALIZATION_CONTEXT_H
#define JSON_I_SERIALIZATION_CONTEXT_H

#include <WString.h>

namespace Json {

class ISerializationContext {
  public:
      virtual String  getString(String key) const = 0;
      virtual bool    getBool(String key) const = 0;

      virtual void    setType(String type) = 0;
      virtual void    setValue(String key, String value) = 0;
      virtual void    setValue(String key, float value) = 0;
};

}

#endif /* end of include guard: JSON_I_SERIALIZATION_CONTEXT_H */
