#include "SettingsController.hpp"

#include "Core/Memory.hpp"
#include "Core/Format.hpp"

#include <EEPROM.h>

using namespace Core;
using namespace Messaging;
using namespace Services;

namespace {
  static const int COMMIT_DELAY       = 10; // 10 seconds
  static const int EEPROM_COLOR_START = 0;
  static const int EEPROM_COLOR_END   = 2;
  static const int EEPROM_NAME_START  = 5;
  static const int EEPROM_NAME_END    = 36;
}

SettingsController::SettingsController(
  IMessageQueue& messageQueue) :
  messageQueue(messageQueue) {

  EEPROM.begin(64);

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
}


std::string
SettingsController::getDeviceName() const {
  std::string name;
  for (size_t i = EEPROM_NAME_START; i <= EEPROM_NAME_END; i++) {
    auto ch = EEPROM.read(i);
    if (ch != 0 && ch > 31 && ch < 127)
      name += ch;
  }
  return name;
}

bool
SettingsController::setDeviceName(std::string name) {
  bool updated = false;
  for (size_t i = EEPROM_NAME_START; i <= EEPROM_NAME_END; i++) {
    char ch = 0;
    size_t index = i - EEPROM_NAME_START;
    if (index < name.length()) {
      ch = name[index];
      if (ch != EEPROM.read(i)) {
        EEPROM.write(i, ch);
        updated = true;
      }
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
  return std::make_unique<Models::Settings>(getDeviceName());
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
