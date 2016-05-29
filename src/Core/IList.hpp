// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_I_LIST_H
#define CORE_I_LIST_H

#include "IEntity.hpp"

#include <functional>

namespace Core {

class IList : public IEntity {
  public:
    virtual ~IList() {};

    typedef std::function<void(const IEntity& item)> ForEachFunction;
    virtual void forEach(ForEachFunction func) const = 0;
};

}

#endif /* end of include guard: CORE_I_LIST_H */
