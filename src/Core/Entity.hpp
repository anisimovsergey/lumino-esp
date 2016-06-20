// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_ENTITY_HPP
#define CORE_ENTITY_HPP

#include "IEntity.hpp"

namespace Core {

template<class T> class Entity : public IEntity {
  public:
    String getTypeId() const override {
      return T::getStaticTypeId();
    }
};

}

#endif /* end of include guard: CORE_ENTITY_HPP */
