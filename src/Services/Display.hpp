// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef SERVICES_DISPLAY_HPP
#define SERVICES_DISPLAY_HPP

#include "Core/IService.hpp"
#include "Models/Connection.hpp"
#include "Messaging/IMessageQueue.hpp"
#include "Messaging/QueueResourceClient.hpp"

#include <memory>

class Adafruit_NeoPixel;

namespace Services {

class Display : public Core::IService  {
  TYPE_PTRS(Display)
  public:
    Display(Messaging::IMessageQueue::Shared messageQueue);

    // From IService
    virtual void idle() override;

  private:
    Messaging::IMessageQueue::Shared messageQueue;
    Messaging::QueueResourceClient::Unique client;
    std::unique_ptr<Adafruit_NeoPixel, void (*)(Adafruit_NeoPixel *)> pixels;

    void colorWipe(uint32_t color);
    void updateConnectionStatus(const Models::Connection& connection);

    // Events
    void onConnectionGetStatusResponse(const Core::Status& status);
    void onConnectionGetResponse(const Models::Connection& connection);
    void onConnectionCreatedEvent(const Models::Connection& connection);
    void onConnectionUpdatedEvent(const Models::Connection& connection);
    void onConnectionDeletedEvent();
};

}

#endif /* end of include guard: SERVICES_DISPLAY_HPP */
