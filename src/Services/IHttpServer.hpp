// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef IHTTPSERVER_H
#define IHTTPSERVER_H

#include <functional>

class IHttpServer {
public:
    typedef std::function<void(void)> THandlerFunction;
    virtual void addGetHandler(const char* uri, THandlerFunction fn) = 0;
    virtual void addPutHandler(const char* uri, THandlerFunction fn) = 0;
};

#endif /* end of include guard: IHTTPSERVER_H */
