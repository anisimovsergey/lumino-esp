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
    static String getStaticTypeId() { return "collection"; }

    String getTypeId() const override {
      return getStaticTypeId();
    }

    void add(const T& value) {
      elements.push_back(value);
    };

    typedef std::function<void(const T& item)> ForEachFunctionTyped;
    void forEach(ForEachFunctionTyped func) const {
        for (auto iterator = elements.begin(),
             end = elements.end();
             iterator != end;
             ++iterator) {
          func(*iterator);
        }
    };

    void forEach(ForEachFunction func) const override {
      forEach([&](const T& element) {
        func(element);
      });
    };

  private:
    std::list<T> elements;
 };

}

#endif /* end of include guard: CORE_LIST_HPP */
