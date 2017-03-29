#include "SettingsController.hpp"

#include "Core/Memory.hpp"
#include "Core/Format.hpp"

#include <ESP8266WiFi.h>
#include <EEPROM.h>

using namespace Core;
using namespace Messaging;
using namespace Services;

namespace {
  static const int COMMIT_DELAY       = 10; // 10 seconds
  static const int EEPROM_COLOR_START = 0;
  static const int EEPROM_UNIQUE_NAME_START  = 5;
  static const int EEPROM_UNIQUE_NAME_LEN    = 32;
  static const int EEPROM_DEVICE_NAME_START  = 40;
  static const int EEPROM_DEVICE_NAME_LEN    = 32;
}

SettingsController::SettingsController(
  IMessageQueue& messageQueue) :
  messageQueue(messageQueue) {

  EEPROM.begin(76);

  settingsController = messageQueue.createController(Models::Settings::TypeId());
  settingsController->addOnRequest(RequestType::Read, [=]() {
    return onGetSettings();
  });
  settingsController->addOnRequest(RequestType::Update, [=](const Models::Settings& model) {
    return onUpdateSettings(model);
  });

  colorController = messageQueue.createController(Models::Color::TypeId());
  colorController->addOnRequest(RequestType::Read, [=](){
    return onGetColor();
  });
  colorController->addOnRequest(RequestType::Update, [=](const Models::Color& model){
    return onUpdateColor(model);
  });

  // Set the uniuqe name to the device name at the first start
  auto uniqueName = getUniqueName();
  if (setUniqueName(uniqueName)) {
    setDeviceName(uniqueName);
  }

  settingsController->sendEvent(EventType::Created, onGetSettings());
  colorController->sendEvent(EventType::Created, onGetColor());
}

std::string
SettingsController::getUniqueName() const {
  // Creating a unique name from the MAC address
  uint8_t macArray[6];
  WiFi.macAddress(macArray);
  uint8_t b1 = macArray[0] ^ macArray[2] ^ macArray[4];
  uint8_t b2 = macArray[1] ^ macArray[3] ^ macArray[5];
  return stringFormat("LUMINO_%02X%02X", b1, b2);
}

bool
SettingsController::setUniqueName(std::string name) {
  return setString(name, EEPROM_UNIQUE_NAME_START, EEPROM_UNIQUE_NAME_LEN);
}

std::string
SettingsController::getDeviceName() const {
  return getString(EEPROM_DEVICE_NAME_START, EEPROM_DEVICE_NAME_LEN);
}

bool
SettingsController::setDeviceName(std::string name) {
  return setString(name, EEPROM_DEVICE_NAME_START, EEPROM_DEVICE_NAME_LEN);
}

std::string
SettingsController::getString(size_t start, size_t len) const {
  std::string name;
  for (size_t i = start;i < start + len; i++) {
    auto ch = EEPROM.read(i);
    if (ch != 0)
      name += ch;
  }
  return name;
}

bool
SettingsController::setString(std::string str, size_t start, size_t len) {
  bool updated = false;
  for (size_t i = start; i < start + len; i++) {
    char ch = 0;
    size_t index = i - start;
    if (index < str.length()) {
      ch = str[index];
    }
    if (ch != EEPROM.read(i)) {
      EEPROM.write(i, ch);
      updated = true;
    }
  }
  if (updated) {
    startCommitTimer();
  }
  return updated;
}

Models::Color
SettingsController::getColor() const {
  int address = EEPROM_COLOR_START;
  auto r = EEPROM.read(address++);
  auto g = EEPROM.read(address++);
  auto b = EEPROM.read(address++);
  return Models::Color(r, g, b);
}

bool
SettingsController::setColor(const Models::Color& color) {
  int address = EEPROM_COLOR_START;
  bool updated = false;
  auto r = EEPROM.read(address);
  if (r != color.getR()) {
    EEPROM.write(address, color.getR());
    updated = true;
  }
  auto g = EEPROM.read(++address);
  if (g != color.getG()) {
    EEPROM.write(address, color.getG());
    updated = true;
  }
  auto b = EEPROM.read(++address);
  if (b != color.getB()) {
    EEPROM.write(address, color.getB());
    updated = true;
  }
  if (updated) {
    startCommitTimer();
  }
  return updated;
}

std::unique_ptr<Core::IEntity>
SettingsController::onGetSettings() {
  return std::make_unique<Models::Settings>(getUniqueName(), getDeviceName());
}

std::unique_ptr<IEntity>
SettingsController::onUpdateSettings(const Models::Settings& settings) {
  if (setDeviceName(settings.getDeviceName())) {
    settingsController->sendEvent(EventType::Updated, std::make_unique<Models::Settings>(settings));
  }
  return std::make_unique<Status>(Status::OK);
}

std::unique_ptr<Core::IEntity>
SettingsController::onGetColor() {
  return std::make_unique<Models::Color>(getColor());
}

std::unique_ptr<Core::IEntity>
SettingsController::onUpdateColor(const Models::Color& color) {
  if (setColor(color)) {
    colorController->sendEvent(EventType::Updated, std::make_unique<Models::Color>(color));
  }
  return std::make_unique<Status>(Status::OK);
}

void
SettingsController::onCommitStatic(SettingsController* controller) {
  controller->onCommitTimeout();
}

void
SettingsController::startCommitTimer() {
  commitTimer.once(COMMIT_DELAY, onCommitStatic,  this);
}

void
SettingsController::onCommitTimeout() {
  EEPROM.commit();
}
