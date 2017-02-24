// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_LOGGER_HPP
#define CORE_LOGGER_HPP

#include "Core/ILogger.hpp"

namespace Core {

class Logger : public Core::ILogger  {
  public:
    Logger();
    virtual void message(const std::string& message) override;
    virtual void warning(const std::string& warning) override;
    virtual void error(const std::string& error) override;
};

}

#endif /* end of include guard: CORE_LOGGER_HPP */
