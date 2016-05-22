// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef ISERIALIZATIONCONTEXT_H
#define ISERIALIZATIONCONTEXT_H

#include <WString.h>

class ISerializationContext {
public:
  virtual String getString(String key) = 0;
};

#endif /* end of include guard: ISERIALIZATIONCONTEXT_H */
