/*
MIT License
Copyright (c) 2019-2022 Sven Lukas

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

#include <esl/com/http/server/exception/StatusCode.h>

namespace esl {
namespace com {
namespace http {
namespace server {
namespace exception {

namespace {

static constexpr const char* messageDefault = "esl::com::http::server::StatusCode error";
static constexpr const char* message1xx = "informational response";
static constexpr const char* message2xx = "successful";
static constexpr const char* message3xx = "redirection";
static constexpr const char* message4xx = "client error";
static constexpr const char* message5xx = "server error";
}

StatusCode::StatusCode(unsigned short aStatusCode)
: std::runtime_error(getMessage(aStatusCode)),
  statusCode(aStatusCode),
  mimeType(utility::MIME::Type::textHtml)
{ }

StatusCode::StatusCode(unsigned short aStatusCode, const char* message)
: std::runtime_error(message ? message : getMessage(aStatusCode)),
  statusCode(aStatusCode),
  mimeType(utility::MIME::Type::textHtml)
{ }

StatusCode::StatusCode(unsigned short aStatusCode, const std::string& message)
: std::runtime_error(message),
  statusCode(aStatusCode),
  mimeType(utility::MIME::Type::textHtml)
{ }

StatusCode::StatusCode(unsigned short aStatusCode, utility::MIME aMimeType)
: std::runtime_error(getMessage(aStatusCode)),
  statusCode(aStatusCode),
  mimeType(std::move(aMimeType))
{ }

StatusCode::StatusCode(unsigned short aStatusCode, utility::MIME aMimeType, const char* message)
: std::runtime_error(message ? message : getMessage(aStatusCode)),
  statusCode(aStatusCode),
  mimeType(std::move(aMimeType))
{ }

StatusCode::StatusCode(unsigned short aStatusCode, utility::MIME aMimeType, const std::string& message)
: std::runtime_error(message),
  statusCode(aStatusCode),
  mimeType(std::move(aMimeType))
{ }

unsigned short StatusCode::getStatusCode() const noexcept {
	return statusCode;
}

const utility::MIME& StatusCode::getMimeType() const noexcept {
	return mimeType;
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
} /* namespace com */
} /* namespace esl */
