// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_LIST_H
#define CORE_LIST_H

#include "ISerializable.hpp"

namespace Core {

class IList : public ISerializable {
  public:
    virtual ~IList() {};
};

template <class T> class List : public IList {
  public:
    String getTypeId() const override { return "collection"; }

    void add(const T& value) {

    };
 };

}

#endif /* end of include guard: CORE_LIST_H */
