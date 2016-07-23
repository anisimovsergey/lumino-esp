// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_MESSAGE_QUEUE_HPP
#define CORE_MESSAGE_QUEUE_HPP

#include "IMessageQueue.hpp"

#include <queue>
#include <list>
#include <vector>
#include <functional>

namespace Core {

class MessageQueue : public IMessageQueue {
  public:
    // From ILoopedService
    virtual void loop() override;

    // From IMessageQueue
    virtual void addClient(QueueClient::Shared client) override;
    virtual void addController(QueueController::Shared controller) override;

  private:
    class MessageComparer {
        bool reverse;
      public:
        bool operator() (const Message::Shared& lhs, const Message::Shared&rhs) const
        {
          return (lhs->getPriority() > rhs->getPriority());
        }
    };

    std::priority_queue<Message::Shared, std::vector<Message::Shared>, MessageComparer> messages;
    std::list<QueueClient::Shared> clients;
    std::list<QueueController::Shared> controllers;

    QueueClient::Shared getClient(String clientId);
    QueueController::Shared getController(const Request& request);
};

}

#endif /* end of include guard: CORE_MESSAGE_QUEUE_HPP */
