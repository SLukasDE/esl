/*
MIT License
Copyright (c) 2019-2021 Sven Lukas

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

#include <esl/com/http/client/Request.h>

namespace esl {
namespace com {
namespace http {
namespace client {

Request::Request(std::string aPath, utility::HttpMethod aMethod, utility::MIME aContentType,
		std::initializer_list<std::pair<const std::string, std::string>> aRequestHeaders)
: path(std::move(aPath)),
  method(std::move(aMethod)),
  contentType(std::move(aContentType)),
  requestHeaders(aRequestHeaders)
{ }

Request::Request(std::string aPath, utility::HttpMethod aMethod, utility::MIME aContentType,
		std::map<std::string, std::string> aRequestHeaders)
: path(std::move(aPath)),
  method(std::move(aMethod)),
  contentType(std::move(aContentType)),
  requestHeaders(std::move(aRequestHeaders))
{ }

const std::string& Request::getPath() const noexcept {
	return path;
}

const utility::HttpMethod& Request::getMethod() const noexcept {
	return method;
}

const utility::MIME& Request::getContentType() const noexcept {
	return contentType;
}

const std::map<std::string, std::string>& Request::getHeaders() const noexcept {
	return requestHeaders;
}

void Request::addHeader(const std::string& key, const std::string& value) {
	requestHeaders[key] = value;
}

} /* namespace client */
} /* namespace http */
} /* namespace com */
} /* namespace esl */
