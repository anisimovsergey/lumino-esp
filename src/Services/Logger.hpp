// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_LOGGER_HPP
#define SERVICES_LOGGER_HPP

#include "Core/ILogger.hpp"

#include <string>

namespace Services {

class Logger : public Core::ILogger  {
  public:
    Logger();
    virtual void idle() override {};
    virtual void message(const std::string& message) override;
    virtual void warning(const std::string& warning) override;
    virtual void error(const std::string& error) override;
};

}

#endif /* end of include guard: SERVICES_LOGGER_HPP */
