// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_I_SERIALIZABLE_H
#define CORE_I_SERIALIZABLE_H

#include <WString.h>

namespace Core {

class ISerializable {
  public:
    virtual String getTypeId() const = 0;
};

}

#endif /* end of include guard: CORE_I_SERIALIZIBLE_H */
