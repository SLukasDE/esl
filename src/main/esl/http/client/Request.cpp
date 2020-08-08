/*
MIT License
Copyright (c) 2019, 2020 Sven Lukas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <esl/http/client/Request.h>
#include <esl/http/client/ResponseHandler.h>

namespace esl {
namespace http {
namespace client {

Request::Request(std::string aPath, utility::HttpMethod aMethod,
		ResponseHandler* aResponseHandler,
		std::unique_ptr<RequestHandler> aRequestHandler,
		std::initializer_list<std::pair<const std::string, std::string>> aRequestHeaders)
: path(std::move(aPath)),
  method(std::move(aMethod)),
  responseHandler(aResponseHandler),
  requestHandler(std::move(aRequestHandler)),
  requestHeaders(aRequestHeaders)
{ }

Request::Request(std::string aPath, utility::HttpMethod aMethod,
		ResponseHandler* aResponseHandler,
		std::unique_ptr<RequestHandler> aRequestHandler,
		std::map<std::string, std::string> aRequestHeaders)
: path(std::move(aPath)),
  method(std::move(aMethod)),
  responseHandler(aResponseHandler),
  requestHandler(std::move(aRequestHandler)),
  requestHeaders(std::move(aRequestHeaders))
{ }

Request::Request(Request&& other)
: path(std::move(other.path)),
  method(std::move(other.method)),
  responseHandler(other.responseHandler),
  requestHandler(std::move(other.requestHandler)),
  requestHeaders(std::move(other.requestHeaders))
{
}

Request::~Request() {
	if(responseHandler) {
		responseHandler->consumeStop();
	}
}

Request& Request::operator=(Request&& other) {
	path = std::move(other.path);
	method = std::move(other.method);
	responseHandler = other.responseHandler;
	other.responseHandler = nullptr;
	requestHandler = std::move(other.requestHandler);
	requestHeaders = std::move(other.requestHeaders);

	return *this;
}

const std::string& Request::getPath() const noexcept {
	return path;
}

const utility::HttpMethod& Request::getMethod() const noexcept {
	return method;
}

RequestHandler* Request::getRequestHandler() const noexcept {
	return requestHandler.get();
}

ResponseHandler* Request::getResponseHandler() const noexcept {
	return responseHandler;
}

const std::map<std::string, std::string>& Request::getHeaders() const noexcept {
	return requestHeaders;
}

void Request::addHeader(const std::string& key, const std::string& value) {
	requestHeaders[key] = value;
}

void Request::setResponse(const Response& response) {
	if(responseHandler) {
		responseHandler->consumeStart(*this, response);
	}
}

} /* namespace client */
} /* namespace http */
} /* namespace esl */
