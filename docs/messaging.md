# Messages

All the messages in the system are divided into four types:
1. "Get" messages
2. "Create" messages
3. "Update" messages
4. "Delete" messages

All the messages are processed asynchronously and the message immediate response should contain the result of the message scheduling only.

## Internal message processing
All the messages are added to the message queue and processed in FIFO order. The message prioritization is not supported.

All the message are divided into two groups, `unicast` messages and `multicast` messages.

|Message type|Request|Response|Notification|
|---------|:-------:|:--------:|:------------:|
|`get`|`unicast`|`unicast`|`unicast`|
|`create`|`unicast`|`unicast`|`multicast`|
|`update`|`unicast`|`unicast`|`multicast`|
|`delete`|`unicast`|`unicast`|`multicast`|

The following properties should be defined for the messages

|Message type|Request|Response|Notification|
|---------|:-------:|:--------:|:------------:|
|`get`|`sender`|`sender`,`receiver`|`sender`,`receiver`|
|`create`|`sender`|`sender`,`receiver`|`sender`|
|`update`|`sender`|`sender`,`receiver`|`sender`|
|`delete`|`sender`|`sender`,`receiver`|`sender`|

When a service sends a `request` message in has to specify itself as the `sender`. In this way `receiver` field is automatically populated when the service which processes the `request` creates a `unicast` `response` or `notification` message.

The message queue processing (message pump):
1. The message is crated by a service and added to the message queue.
2. All the services with the message handler registered in the message pump are sequentially notified about the new message in the queue.
3. If a service can process the message it does the processing and returns the result of the processing to the message pump.
4. If the message is a unicast message the message gets removed from the queue and the result of the processing is added into it in a form of a response message.
5. If the message is a multicast message the message is not removed from the queue so the next service can get a chance to process it.
6. When all the services are requested to process the message and message is still in the queue, it gets removed automatically at the end of a message pump loop cycle.
7. If the message queue contains another message the message pumping cycle repeats.
