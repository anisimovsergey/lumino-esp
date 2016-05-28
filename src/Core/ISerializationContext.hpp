// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_I_SERIALIZATION_CONTEXT_H
#define CORE_I_SERIALIZATION_CONTEXT_H

#include "IList.hpp"

#include <WString.h>

namespace Core {

class ISerializationContext {
  public:
      virtual ~ISerializationContext() {};

      virtual void    setValue(String key, String value) = 0;
      virtual void    setValue(String key, int value) = 0;
      virtual void    setValue(String key, const IList& list) = 0;
};

}

#endif /* end of include guard: CORE_I_SERIALIZATION_CONTEXT_H */
