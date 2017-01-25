// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_LOGGER_HPP
#define SERVICES_LOGGER_HPP

#include "Core/ILogger.hpp"

namespace Services {

class Logger : public Core::ILogger  {
  TYPE_PTRS(Logger)
  public:
    Logger();

  private:
    virtual void message(const std::string& message) override;
    virtual void warning(const std::string& message) override;
    virtual void error(const std::string& message) override;
};

}

#endif /* end of include guard: SERVICES_LOGGER_HPP */
