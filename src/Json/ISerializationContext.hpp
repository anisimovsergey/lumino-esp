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
  TYPE_PTRS(ISerializationContext)
  public:
    virtual ~ISerializationContext();

    virtual String toString() const = 0;

    virtual bool hasKey(const String& key) = 0;

    virtual Core::StatusResult::Unique
      getStringValue(const String& key, String& value) = 0;
    virtual Core::StatusResult::Unique
      getBoolValue(const String& key, bool& value) = 0;
    virtual Core::StatusResult::Unique
      getEntity(const String& key, Core::IEntity::Unique& entity) = 0;

    virtual Core::StatusResult::Unique
      setValue(const String& key, const String& value) = 0;
    virtual Core::StatusResult::Unique
      setValue(const String& key, int value) = 0;
    virtual Core::StatusResult::Unique
      setValue(const String& key, bool value) = 0;
    virtual Core::StatusResult::Unique
      setValue(const String& key, const Core::IList& list) = 0;
    virtual Core::StatusResult::Unique
      setValue(const String& key, const Core::IEntity& entity) = 0;
};

}

#endif /* end of include guard: SERVICES_I_SERIALIZATION_CONTEXT_HPP */
