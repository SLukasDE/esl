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

#ifndef ESL_HTTP_CLIENT_RESPONSE_H_
#define ESL_HTTP_CLIENT_RESPONSE_H_

#include <esl/utility/MIME.h>

#include <string>
#include <map>

namespace esl {
namespace http {
namespace client {

class Response final {
public:
	Response() = default;
	Response(unsigned short statusCode, std::map<std::string, std::string> headers);

	const std::map<std::string, std::string>& getHeaders() const noexcept;
	const utility::MIME& getContentType() const noexcept;
	unsigned short getStatusCode() const noexcept;

private:
	std::map<std::string, std::string> headers;
	utility::MIME contentType;
	unsigned short statusCode = 0;
};

} /* namespace client */
} /* namespace http */
} /* namespace esl */

#endif /* ESL_HTTP_CLIENT_RESPONSE_H_ */
