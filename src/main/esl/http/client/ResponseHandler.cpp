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

#include <esl/http/client/ResponseHandler.h>
#include <esl/http/client/Request.h>
#include <esl/http/client/Response.h>

namespace esl {
namespace http {
namespace client {

namespace {
const Request defaultRequest("", utility::HttpMethod(), nullptr, nullptr, {});
const Response defaultResponse(0, {});
}

ResponseHandler::ResponseHandler()
: request(std::cref(defaultRequest)),
  response(std::cref(defaultResponse))
{ }

const Request& ResponseHandler::getRequest() const noexcept {
	return request.get();
}

const Response& ResponseHandler::getResponse() const noexcept {
	return response.get();
}

void ResponseHandler::consumeStart(const Request& aRequest, const Response& aResponse) noexcept {
	request = std::cref(aRequest);
	response = std::cref(aResponse);
}

void ResponseHandler::consumeStop() noexcept {
	request = std::cref(defaultRequest);
	response = std::cref(defaultResponse);
}

} /* namespace client */
} /* namespace http */
} /* namespace esl */
