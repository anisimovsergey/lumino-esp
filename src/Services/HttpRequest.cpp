#include "HttpRequest.hpp"

#include "HttpResponse.hpp"
#include "Core/Logger.hpp"

#include <ESPAsyncWebServer.h>

#include <memory>
#include <type_traits>
#include <utility>

template <typename T, typename... Args>
std::unique_ptr<T> make_unique_helper(std::false_type, Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T, typename... Args>
std::unique_ptr<T> make_unique_helper(std::true_type, Args&&... args) {
   static_assert(std::extent<T>::value == 0,
       "make_unique<T[N]>() is forbidden, please use make_unique<T[]>().");

   typedef typename std::remove_extent<T>::type U;
   return std::unique_ptr<T>(new U[sizeof...(Args)]{std::forward<Args>(args)...});
}

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
   return make_unique_helper<T>(std::is_array<T>(), std::forward<Args>(args)...);
}

using namespace Core;
using namespace Services;

HttpRequest::HttpRequest(
  AsyncWebServerRequest& request) :
  request(request) {
}

HttpRequest::~HttpRequest() {
}

String
HttpRequest::getArgument(String argument) {
  return request.arg(argument.c_str());
}

String
HttpRequest::getHeader(String header) {
  return request.header(header.c_str());
}

std::unique_ptr<IHttpResponse>
HttpRequest::createResponse(int code) {
  auto response = request.beginResponse(code);
  std::unique_ptr<IHttpResponse> a(new HttpResponse(request, *response));
  return a;
}

std::unique_ptr<IHttpResponse>
HttpRequest::createResponse(
  int code, String contentType, String content) {
  auto response = request.beginResponse(code, contentType, content);
  auto  a = make_unique<HttpResponse>(request, *response);
  return a;
}
