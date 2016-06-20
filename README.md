# A night lamp project

A night lamp remotely controlled using ESP8266.

## YAFF (yet another framework)

The framework is allowing you to write REST API fast and reliably.

Core framework abstractions.
* Models
* Controllers
* Serializers
* Senders

### Architectural
No RTTI, no exceptions

### The lifetime of a request.
* HTTP server accepts an HTTP request.
* HTTP server finds a handler.
* server deserializes body (for POST and PUT requests).
* handler is called with the request.
* handler replies with an action result.
* server tries to find a sender for the action result.
* the sender serializers the action result (if needed).
* the sender creates a response and sends it to the client.

##License

Copyright (c) 2016 Sergey Anisimov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
