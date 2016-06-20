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
