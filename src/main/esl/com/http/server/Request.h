/*
MIT License
Copyright (c) 2019-2025 Sven Lukas

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

#ifndef ESL_COM_HTTP_SERVER_REQUEST_H_
#define ESL_COM_HTTP_SERVER_REQUEST_H_

#include <esl/utility/MIME.h>
#include <esl/utility/HttpMethod.h>

#include <map>
#include <string>
#include <cstdint>

namespace esl {
inline namespace v1_6 {
namespace com {
namespace http {
namespace server {

class Request {
public:
	virtual ~Request() = default;

	virtual bool isHTTPS() const noexcept = 0;
	virtual const std::string& getHTTPVersion() const noexcept = 0;

	virtual const std::string& getHostName() const noexcept = 0;
	virtual const std::string& getHostAddress() const noexcept = 0;
	virtual uint16_t getHostPort() const noexcept = 0;

	virtual const std::string& getRemoteAddress() const noexcept = 0;
	virtual uint16_t getRemotePort() const noexcept = 0;

	virtual const std::string& getPath() const noexcept = 0;
	virtual const utility::HttpMethod& getMethod() const noexcept = 0;
	virtual const std::map<std::string, std::string>& getHeaders() const noexcept = 0;
	virtual const utility::MIME& getContentType() const noexcept = 0;

	virtual bool hasArgument(const std::string& key) const noexcept = 0;
	virtual const std::string& getArgument(const std::string& key) const = 0;
};

} /* namespace server */
} /* namespace http */
} /* namespace com */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_COM_HTTP_SERVER_REQUEST_H_ */
