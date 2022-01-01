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

#ifndef ESL_COM_HTTP_SERVER_RESPONSE_H_
#define ESL_COM_HTTP_SERVER_RESPONSE_H_

#include <esl/utility/MIME.h>

#include <string>
#include <map>

namespace esl {
namespace com {
namespace http {
namespace server {

class Response {
public:
	Response(unsigned short statusCode, const utility::MIME& contentType, std::string realmId = "") noexcept;
	virtual ~Response() = default;

	unsigned short getStatusCode() const noexcept;

	const std::string& getRealmId() const noexcept;

	void addHeader(const std::string& key, const std::string& value);
	const std::map<std::string, std::string>& getHeaders() const;

private:
	std::map<std::string, std::string> headers;
	unsigned short statusCode;
	std::string realmId;
};

} /* namespace server */
} /* namespace http */
} /* namespace com */
} /* namespace esl */

#endif /* ESL_COM_HTTP_SERVER_RESPONSE_H_ */
