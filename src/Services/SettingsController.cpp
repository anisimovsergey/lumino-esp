#include "SettingsController.hpp"

#include "Core/Memory.hpp"

#include <EEPROM.h>

using namespace Core;
using namespace Messaging;
using namespace Services;

namespace {
  static const int EEPROM_COLOR_START = 0;
  static const int EEPROM_COLOR_END   = 2;
  static const int EEPROM_NAME_START  = 5;
  static const int EEPROM_NAME_END    = 36;
}

SettingsController::SettingsController(
  Messaging::IMessageQueue& messageQueue) :
  messageQueue(messageQueue) {

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
    if (ch != 0)
      name += ch;
  }
  return name;
}

void
SettingsController::setDeviceName(std::string name) {
  for (size_t i = EEPROM_NAME_START; i <= EEPROM_NAME_END; i++) {
    char ch = 0;
    size_t index = i - EEPROM_NAME_START;
    if (index < name.length())
      ch = name[index];
    EEPROM.write(i, ch);
  }
}

Models::Color
SettingsController::getColor() const {
  int address = EEPROM_COLOR_START;
  auto r = EEPROM.read(address++);
  auto g = EEPROM.read(address++);
  auto b = EEPROM.read(address++);
  return Models::Color(r, g, b);
}

void
SettingsController::setColor(const Models::Color& color) {
  int address = EEPROM_COLOR_START;
  EEPROM.write(address++, color.getR());
  EEPROM.write(address++, color.getG());
  EEPROM.write(address++, color.getB());
}

std::unique_ptr<Core::IEntity>
SettingsController::onGetSettings() {
  return std::make_unique<Models::Settings>(getDeviceName());
}

std::unique_ptr<IEntity>
SettingsController::onUpdateSettings(const Models::Settings& model) {
  setDeviceName(model.getDeviceName());
  settingsController->sendEvent(EventType::Updated, std::make_unique<Models::Settings>(model));
  return std::make_unique<Status>(Status::OK);
}

std::unique_ptr<Core::IEntity>
SettingsController::onGetColor() {
  return std::make_unique<Models::Color>(getColor());
}

std::unique_ptr<Core::IEntity>
SettingsController::onUpdateColor(const Models::Color& model) {
  setColor(model);
  colorController->sendEvent(EventType::Updated, std::make_unique<Models::Color>(model));
  return std::make_unique<Status>(Status::OK);
}
