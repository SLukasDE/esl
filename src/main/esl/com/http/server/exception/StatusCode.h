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

#ifndef ESL_COM_HTTP_SERVER_EXCEPTION_STATUSCODE_H_
#define ESL_COM_HTTP_SERVER_EXCEPTION_STATUSCODE_H_

#include <esl/utility/MIME.h>

#include <stdexcept>
#include <string>

namespace esl {
namespace com {
namespace http {
namespace server {
namespace exception {

class StatusCode : public std::runtime_error {
public:
	explicit StatusCode(unsigned short statusCode);
	explicit StatusCode(unsigned short statusCode, const char* message);
	explicit StatusCode(unsigned short statusCode, const std::string& message);

	explicit StatusCode(unsigned short statusCode, utility::MIME mimeType);
	explicit StatusCode(unsigned short statusCode, utility::MIME mimeType, const char* message);
	explicit StatusCode(unsigned short statusCode, utility::MIME mimeType, const std::string& message);

	unsigned short getStatusCode() const noexcept;
	const utility::MIME& getMimeType() const noexcept;

	static const char* getMessage(short int statusCode) noexcept;

private:
	unsigned short statusCode;
	utility::MIME mimeType;
};

} /* namespace exception */
} /* namespace server */
} /* namespace http */
} /* namespace com */
} /* namespace esl */

#endif /* ESL_COM_HTTP_SERVER_EXCEPTION_STATUSCODE_H_ */
