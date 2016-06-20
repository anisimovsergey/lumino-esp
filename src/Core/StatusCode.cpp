#include "StatusCode.hpp"

using namespace Core;

const StatusCode StatusCode::OK =
  StatusCode(200, "OK");
const StatusCode StatusCode::Created =
  StatusCode(201, "Created");
const StatusCode StatusCode::NoContent =
  StatusCode(204, "NoContent");
const StatusCode StatusCode::Redirect =
  StatusCode(302, "Redirect");
const StatusCode StatusCode::BadRequest =
  StatusCode(400, "BadRequest");
const StatusCode StatusCode::NotFound =
  StatusCode(404, "NotFound");
const StatusCode StatusCode::Conflict =
  StatusCode(409, "Conflict");
const StatusCode StatusCode::InternalServerError =
  StatusCode(500, "InternalServerError");
const StatusCode StatusCode::NotImplemented =
  StatusCode(500, "NotImplemented");

const StatusCode StausCode::Continue = 100,
const StatusCode StausCode::SwitchingProtocols = 101,
const StatusCode StausCode::OK = 200,
const StatusCode StausCode::Created = 201,
const StatusCode StausCode::Accepted = 202,
const StatusCode StausCode::NonAuthoritativeInformation = 203,
const StatusCode StausCode::NoContent = 204,
const StatusCode StausCode::ResetContent = 205,
const StatusCode StausCode::PartialContent = 206,
const StatusCode StausCode::MultipleChoices = 300,
const StatusCode StausCode::Ambiguous = 300,
const StatusCode StausCode::MovedPermanently = 301,
const StatusCode StausCode::Moved = 301,
const StatusCode StausCode::Found = 302,
const StatusCode StausCode::Redirect = 302,
const StatusCode StausCode::SeeOther = 303,
const StatusCode StausCode::RedirectMethod = 303,
const StatusCode StausCode::NotModified = 304,
const StatusCode StausCode::UseProxy = 305,
const StatusCode StausCode::Unused = 306,
const StatusCode StausCode::RedirectKeepVerb = 307,
const StatusCode StausCode::TemporaryRedirect = 307,
const StatusCode StausCode::BadRequest = 400,
const StatusCode StausCode::Unauthorized = 401,
const StatusCode StausCode::PaymentRequired = 402,
const StatusCode StausCode::Forbidden = 403,
const StatusCode StausCode::NotFound = 404,
const StatusCode StausCode::MethodNotAllowed = 405,
const StatusCode StausCode::NotAcceptable = 406,
const StatusCode StausCode::ProxyAuthenticationRequired = 407,
const StatusCode StausCode::RequestTimeout = 408,
const StatusCode StausCode::Conflict = 409,
const StatusCode StausCode::Gone = 410,
const StatusCode StausCode::LengthRequired = 411,
const StatusCode StausCode::PreconditionFailed = 412,
const StatusCode StausCode::RequestEntityTooLarge = 413,
const StatusCode StausCode::RequestUriTooLong = 414,
const StatusCode StausCode::UnsupportedMediaType = 415,
const StatusCode StausCode::RequestedRangeNotSatisfiable = 416,
const StatusCode StausCode::ExpectationFailed = 417,
const StatusCode StausCode::UpgradeRequired = 426,
const StatusCode StausCode::InternalServerError = 500,
const StatusCode StausCode::NotImplemented = 501,
const StatusCode StausCode::BadGateway = 502,
const StatusCode StausCode::ServiceUnavailable = 503,
const StatusCode StausCode::GatewayTimeout = 504,
const StatusCode StausCode::HttpVersionNotSupported = 505,
