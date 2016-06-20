# A night lamp project

A night lamp remotely controlled using ESP8266.

## YAFF (yet another framework)

The framework is allowing you to write REST API fast and reliably.

Core framework abstractions.
* Models
* Controllers
* Serializers
* Senders

### The lifetime of a request.
* HTTP server accepts an HTTP request.
* HTTP server finds a handler.
* server deserializes body (for POST and PUT requests).
* handler is called with the request.
* handler replies with an action result.
* server tries to find a sender for the action result.
* the sender serializers the action result (if needed).
* the sender creates a response and sends it to the client.
