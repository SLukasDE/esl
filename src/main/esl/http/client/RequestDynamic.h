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

#include <esl/http/client/Request.h>
#include <string>

#ifndef SRC_ESL_HTTP_CLIENT_REQUESTDYNAMIC_H_
#define SRC_ESL_HTTP_CLIENT_REQUESTDYNAMIC_H_

namespace esl {
namespace http {
namespace client {

class RequestDynamic : public Request {
public:
	RequestDynamic(const std::string& servicePath, const std::string& contentType);
	~RequestDynamic() = default;

	virtual std::size_t write(void* data, std::size_t size) = 0;
};

} /* namespace client */
} /* namespace http */
} /* namespace esl */

#endif /* SRC_ESL_HTTP_CLIENT_REQUESTDYNAMIC_H_ */
