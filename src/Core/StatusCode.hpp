// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_STATUS_CODE_HPP
#define CORE_STATUS_CODE_HPP

#include <WString.h>

namespace Core {

class StatusCode {
  public:
    static const StatusCode OK;
    static const StatusCode Created;
    static const StatusCode NoContent;
    static const StatusCode Redirect;
    static const StatusCode BadRequest;
    static const StatusCode NotFound;
    static const StatusCode Conflict;
    static const StatusCode InternalServerError;
    static const StatusCode NotImplemented;

    int     getCode() const { return code; }
    String  getText() const { return text; }

    bool operator==(const StatusCode& other) const {
      return code == other.code;
    }

    bool operator!=(const StatusCode& other) const {
      return !(*this == other);
    }

  private:
    StatusCode(int code, String text) : code(code), text(text) {
    }

    int     code;
    String  text;
};

}

#endif /* end of include guard: CORE_STATUS_CODE_HPP */
