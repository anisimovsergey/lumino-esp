// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_LOGGER_HPP
#define CORE_LOGGER_HPP

#include <WString.h>

namespace Core {

class Logger {
  public:
    static void initialize();

    static void message(const String& message);
    static void warning(const String& message);
    static void error(const String& message);
};

}

#endif /* end of include guard: CORE_LOGGER_HPP */
