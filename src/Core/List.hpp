// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_LIST_HPP
#define CORE_LIST_HPP

#include "IList.hpp"

#include <list>

namespace Core {

template <class T> class List : public IList {
  public:
    static String getStaticTypeId() { return "list"; }

    // From IEntity
    String getTypeId() const override {
      return getStaticTypeId();
    }

    // From IList
    virtual std::unique_ptr<Core::StatusResult> add(
      const IEntity& item) const override {
      return add((const T&)item);
    }

    virtual std::unique_ptr<Core::StatusResult>
      forEach(ForEachFunction func) const override {
      return forEach([&](const T& element) {
        return func(element);
      });
    };

    std::unique_ptr<Core::StatusResult> add(const T& value) {
      elements.push_back(value);
      return Core::StatusResult::OK();
    };

    typedef std::function<std::unique_ptr<Core::StatusResult>
      (const T& item)> ForEachFunctionTyped;

    std::unique_ptr<Core::StatusResult> forEach(
      ForEachFunctionTyped func) const {
        for (auto iterator = elements.begin(), end = elements.end();
             iterator != end; ++iterator) {
          auto result = func(*iterator);
          if (result->isOk())
            return result;
        }
        return Core::StatusResult::OK();
    };

  private:
    std::list<T> elements;
 };

}

#endif /* end of include guard: CORE_LIST_HPP */
