// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_LIST_H
#define CORE_LIST_H

#include "ISerializable.hpp"

#include <list>
#include <functional>

namespace Core {

class IList : public ISerializable {
  public:
    virtual ~IList() {};

    typedef std::function<void(const ISerializable& item)> ForEachFunction;
    virtual void forEach(ForEachFunction func) const = 0;
};

template <class T> class List : public IList {
  public:
    String getTypeId() const override { return "collection"; }

    void add(const T& value) {
      elements.push_back(value);
    };

    void forEach(ForEachFunction func) const {
      for (auto iterator = elements.begin(),
           end = elements.end();
           iterator != end;
           ++iterator) {
        func(*iterator);
      }
    }

  private:
    std::list<T> elements;
 };

}

#endif /* end of include guard: CORE_LIST_H */
