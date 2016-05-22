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
    virtual String  getString(String key) const = 0;
    virtual bool    getBool(String key) const = 0;

    virtual void    setType(String type) = 0;
    virtual void    setValue(String key, String value) = 0;
    virtual void    setValue(String key, float value) = 0;
};

#endif /* end of include guard: ISERIALIZATIONCONTEXT_H */
