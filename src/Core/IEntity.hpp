// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_I_ENTITY_H
#define CORE_I_ENTITY_H

#include <WString.h>

namespace Core {

class IEntity {
  public:
    virtual ~IEntity() {};
    virtual String getTypeId() const = 0;

    template<typename T> T* dynamicCast() {
      if (getTypeId() == T::getStaticTypeId())
        return (T*)(this);

      return nullptr;
    }

    template<typename T> const T* dynamicCast() const {
      if (getTypeId() == T::getStaticTypeId())
        return (T*)(this);

      return nullptr;
    }
};

}

#endif /* end of include guard: CORE_I_ENTITY_H */
