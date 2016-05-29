// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_I_SERIALIZATION_CONTEXT_H
#define JSON_I_SERIALIZATION_CONTEXT_H

#include "Core/IList.hpp"

#include <WString.h>

namespace Json {

class ISerializationContext {
  public:
    virtual ~ISerializationContext() {};

    virtual void setValue(const String& key, const String& value) = 0;
    virtual void setValue(const String& key, int value) = 0;
    virtual void setValue(const String& key, const Core::IList& list) = 0;
};

}

#endif /* end of include guard: SERVICES_I_SERIALIZATION_CONTEXT_H */
