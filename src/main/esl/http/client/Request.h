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

#ifndef SRC_MAIN_C___RSM_SERVICE_CLIENT_REQUEST_H_
#define SRC_MAIN_C___RSM_SERVICE_CLIENT_REQUEST_H_

#include <esl/utility/HttpMethod.h>
#include <esl/utility/MIME.h>

#include <string>
#include <map>

namespace esl {
namespace http {
namespace client {

class Request {
public:
	virtual ~Request() = default;

	const std::string& getPath() const noexcept;
	const utility::HttpMethod& getMethod() const noexcept;
	const utility::MIME& getContentType() const noexcept;

	const std::map<std::string, std::string>& getHeaders() const noexcept;
	void addHeader(const std::string& key, const std::string& value);

protected:
	Request(std::string path, utility::HttpMethod method, utility::MIME contentType);

private:
	std::string path;
	utility::HttpMethod method;
	utility::MIME contentType;

	std::map<std::string, std::string> headers;
};

} /* namespace client */
} /* namespace http */
} /* namespace esl */

#endif /* SRC_MAIN_C___RSM_SERVICE_CLIENT_REQUEST_H_ */
