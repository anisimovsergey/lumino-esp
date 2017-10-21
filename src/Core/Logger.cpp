#include "Logger.hpp"
#include "Core/Format.hpp"

using namespace Core;

#include <HardwareSerial.h>

extern "C" {
  #include "user_interface.h"
}

#define DBG_OUTPUT_PORT Serial

static uint32_t timer = 0;

Logger::Logger() {
  DBG_OUTPUT_PORT.begin(115200);
  DBG_OUTPUT_PORT.setDebugOutput(false);
  DBG_OUTPUT_PORT.println("");
  timer = system_get_time();
}

void
Logger::message(const std::string& message) {
  auto msg = stringFormat("%u, message: %s", system_get_time() - timer, message.c_str());
  DBG_OUTPUT_PORT.println(msg.c_str());
}

void
Logger::warning(const std::string& warning) {
  auto msg = stringFormat("%u, warning: %s", system_get_time() - timer, warning.c_str());
  DBG_OUTPUT_PORT.println(msg.c_str());
}

void
Logger::error(const std::string& error) {
  auto msg = stringFormat("%u, error: %s", system_get_time() - timer, error.c_str());
  DBG_OUTPUT_PORT.println(msg.c_str());
}
