// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_I_SERIALIZATION_CONTEXT_HPP
#define JSON_I_SERIALIZATION_CONTEXT_HPP

#include "Core/ActionResult.hpp"
#include "Core/IList.hpp"

#include <WString.h>

namespace Json {

class ISerializationContext {
  public:
    virtual ~ISerializationContext() {};

    virtual String toString() const = 0;

    virtual std::unique_ptr<Core::StatusResult>
      getStringValue(const String& key, String& value) = 0;
    virtual std::unique_ptr<Core::StatusResult>
      getBoolValue(const String& key, bool& value) = 0;

    virtual void setValue(const String& key, const String& value) = 0;
    virtual void setValue(const String& key, int value) = 0;
    virtual void setValue(const String& key, bool value) = 0;
    virtual void setValue(const String& key, const Core::IList& list) = 0;
};

}

#endif /* end of include guard: SERVICES_I_SERIALIZATION_CONTEXT_HPP */
