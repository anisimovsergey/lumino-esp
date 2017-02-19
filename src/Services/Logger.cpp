#include "Logger.hpp"

using namespace Core;
using namespace Services;

#include <HardwareSerial.h>

#define DBG_OUTPUT_PORT Serial

Logger::Logger() {
  DBG_OUTPUT_PORT.begin(115200);
  DBG_OUTPUT_PORT.setDebugOutput(false);
  DBG_OUTPUT_PORT.println("");
}

void
Logger::message(const std::string& message) {
  DBG_OUTPUT_PORT.print("MESSAGE: ");
  DBG_OUTPUT_PORT.println(message.c_str());
}

void
Logger::warning(const std::string& warning) {
  DBG_OUTPUT_PORT.print("WARNING: ");
  DBG_OUTPUT_PORT.println(warning.c_str());
}

void
Logger::error(const std::string& error) {
  DBG_OUTPUT_PORT.print("ERROR: ");
  DBG_OUTPUT_PORT.println(error.c_str());
}
