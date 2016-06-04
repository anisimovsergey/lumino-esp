// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_ENTITY_H
#define CORE_ENTITY_H

#include "IEntity.hpp"

namespace Core {

template<class T> class Entity : public IEntity {
  public:
    String getTypeId() const override {
      return T::getStaticTypeId();
    }

    static T* dynamicCast(const IEntity* entity) {

      if (entity == nullptr)
        return nullptr;

      if (entity->getTypeId() == T::getStaticTypeId())
        return (T*)(entity);

      return nullptr;
    }
};

}

#endif /* end of include guard: CORE_ENTITY_H */
