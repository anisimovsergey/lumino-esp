// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_I_LIST_HPP
#define CORE_I_LIST_HPP

#include "IEntity.hpp"
#include "Core/ActionResult.hpp"

#include <functional>

namespace Core {

class IList : public IEntity {
  TYPE_INFO(IList, IEntity, "list")
  public:
    virtual ~IList();

    typedef std::function<Core::StatusResult::Unique
      (const IEntity& item)> ForEachFunction;

    virtual Core::StatusResult::Unique add(
      const IEntity& item) const = 0;
    virtual Core::StatusResult::Unique forEach(
      ForEachFunction func) const = 0;
};

}

#endif /* end of include guard: CORE_I_LIST_HPP */
