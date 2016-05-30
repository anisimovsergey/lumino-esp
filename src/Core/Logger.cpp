#include "Logger.hpp"

using namespace Core;

#include <HardwareSerial.h>

#define DBG_OUTPUT_PORT Serial

void
Logger::initialize() {
  DBG_OUTPUT_PORT.begin(115200);
  DBG_OUTPUT_PORT.setDebugOutput(true);
}

void
Logger::message(const String& message) {
  DBG_OUTPUT_PORT.print("MESSAGE: ");
  DBG_OUTPUT_PORT.print(message);
}

void
Logger::warning(const String& message) {
  DBG_OUTPUT_PORT.print("WARNING: ");
  DBG_OUTPUT_PORT.print(message);
}

void
Logger::error(const String& message) {
  DBG_OUTPUT_PORT.print("ERROR: ");
  DBG_OUTPUT_PORT.print(message);
}
