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
  TYPE_PTRS(MessageQueue)
  public:
    MessageQueue();
    ~MessageQueue();

    // From ILoopedService
    virtual void loop() override;

    // From IMessageQueue
    virtual StatusResult::Unique sendMessage(Message::Shared message) override;

    virtual QueueClient::Shared createClient(std::string clinetId) override;
    virtual void removeClient(QueueClient::Shared client) override;
    virtual QueueController::Shared createController(std::string controllerId) override;
    virtual void removeController(QueueController::Shared controller) override;

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

    void processRequest(const Request& request);
    void processResponse(const Response& response);
    void processNotification(const Notification& notification);

    QueueClient::Shared     getClient(std::string clientId);
    QueueController::Shared getController(const Request& request);
    Response::Shared        createResponseFor(const Request& request,
      ActionResult::Unique result, const QueueController* controller);
};

}

#endif /* end of include guard: CORE_MESSAGE_QUEUE_HPP */
