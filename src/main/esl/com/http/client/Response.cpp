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

#include <esl/com/http/client/Response.h>
#include <esl/utility/String.h>

#include <algorithm>

namespace esl {
namespace com {
namespace http {
namespace client {
namespace {

utility::MIME findContentType(const std::map<std::string, std::string>& headers) {
	for(const auto& entry : headers) {
		if(entry.first == "Content-Type") {
			// Value could be "text/html; charset=UTF-8", so we have to split for ';' character and we take first element
			std::vector<std::string> contentTypes = utility::String::split(utility::String::trim(entry.second), ';');
			if(!contentTypes.empty()) {
				return utility::MIME(utility::String::trim(contentTypes.front()));
			}
			break;
		}
	}
	return utility::MIME();
}

}
Response::Response(unsigned short aStatusCode, std::map<std::string, std::string> aHeaders)
: headers(std::move(aHeaders)),
  contentType(findContentType(headers)),
  statusCode(aStatusCode)
{ }

const utility::MIME& Response::getContentType() const noexcept {
	return contentType;
}

const std::map<std::string, std::string>& Response::getHeaders() const noexcept {
	return headers;
}

unsigned short Response::getStatusCode() const noexcept {
	return statusCode;
}

} /* namespace client */
} /* namespace http */
} /* namespace com */
} /* namespace esl */


