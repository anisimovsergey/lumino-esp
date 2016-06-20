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
    static const StatusCode Continue;
    static const StatusCode SwitchingProtocols;
    static const StatusCode OK;
    static const StatusCode Created;
    static const StatusCode Accepted;
    static const StatusCode NonAuthoritativeInformation;
    static const StatusCode NoContent;
    static const StatusCode ResetContent;
    static const StatusCode PartialContent;
    static const StatusCode MultipleChoices;
    static const StatusCode Ambiguous;
    static const StatusCode MovedPermanently;
    static const StatusCode Moved;
    static const StatusCode Found;
    static const StatusCode Redirect;
    static const StatusCode SeeOther;
    static const StatusCode RedirectMethod;
    static const StatusCode NotModified;
    static const StatusCode UseProxy;
    static const StatusCode Unused;
    static const StatusCode RedirectKeepVerb;
    static const StatusCode TemporaryRedirect;
    static const StatusCode BadRequest;
    static const StatusCode Unauthorized;
    static const StatusCode PaymentRequired;
    static const StatusCode Forbidden;
    static const StatusCode NotFound;
    static const StatusCode MethodNotAllowed;
    static const StatusCode NotAcceptable;
    static const StatusCode ProxyAuthenticationRequired;
    static const StatusCode RequestTimeout;
    static const StatusCode Conflict;
    static const StatusCode Gone;
    static const StatusCode LengthRequired;
    static const StatusCode PreconditionFailed;
    static const StatusCode RequestEntityTooLarge;
    static const StatusCode RequestUriTooLong;
    static const StatusCode UnsupportedMediaType;
    static const StatusCode RequestedRangeNotSatisfiable;
    static const StatusCode ExpectationFailed;
    static const StatusCode UpgradeRequired;
    static const StatusCode InternalServerError;
    static const StatusCode NotImplemented;
    static const StatusCode BadGateway;
    static const StatusCode ServiceUnavailable;
    static const StatusCode GatewayTimeout;
    static const StatusCode HttpVersionNotSupported;

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
