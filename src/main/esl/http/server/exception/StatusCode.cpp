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

#include <esl/http/server/exception/StatusCode.h>

namespace esl {
namespace http {
namespace server {
namespace exception {

namespace {

static constexpr const char* messageDefault = "esl::http::server::StatusCode error";
static constexpr const char* message1xx = "informational response";
static constexpr const char* message2xx = "successful";
static constexpr const char* message3xx = "redirection";
static constexpr const char* message4xx = "client error";
static constexpr const char* message5xx = "server error";
}

StatusCode::StatusCode(short int aStatusCode)
: Exception(getMessage(aStatusCode)),
  statusCode(aStatusCode)
{ }

StatusCode::StatusCode(short int aStatusCode, const char* message)
: Exception(message),
  statusCode(aStatusCode)
{ }

StatusCode::StatusCode(short int aStatusCode, const std::string& message)
: Exception(message),
  statusCode(aStatusCode)
{ }

short int StatusCode::getStatusCode() const noexcept {
	return statusCode;
}

const char* StatusCode::getMessage(short int statusCode) noexcept {
	if(statusCode >= 100 && statusCode <= 199) {
		return message1xx;
	}
	else if(statusCode >= 200 && statusCode <= 299) {
		return message2xx;
	}
	else if(statusCode >= 300 && statusCode <= 399) {
		return message3xx;
	}
	else if(statusCode >= 400 && statusCode <= 499) {
		return message4xx;
	}
	else if(statusCode >= 500 && statusCode <= 599) {
		return message5xx;
	}

	return messageDefault;
}

} /* namespace exception */
} /* namespace server */
} /* namespace http */
} /* namespace esl */
