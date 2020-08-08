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

#ifndef ESL_HTTP_CLIENT_RESPONSEHANDLER_H_
#define ESL_HTTP_CLIENT_RESPONSEHANDLER_H_

//#include <esl/http/client/Request.h>
//#include <esl/http/client/Response.h>
#include <esl/http/client/Interface.h>

#include <string>
#include <functional>

namespace esl {
namespace http {
namespace client {

class Request;
class Response;

class ResponseHandler {
/* to allow calling 'void consumeStart(...)' and 'void consumeStop()' */
friend class Request;

friend class RequestHandler;

/* to allow calling 'bool consumer(...)' */
friend class Interface::Connection;

public:
	ResponseHandler();
	virtual ~ResponseHandler() = default;

protected:
	virtual bool consumer(const char* contentData, std::size_t contentSize) = 0;

	/* should be used only from method 'bool consumer(...)' */
	const Request& getRequest() const noexcept;

	/* should be used only from method 'bool consumer(...)' */
	const Response& getResponse() const noexcept;

private:
	void consumeStart(const Request& request, const Response& response) noexcept;
	void consumeStop() noexcept;

	std::reference_wrapper<const Request> request;
	std::reference_wrapper<const Response> response;
};

} /* namespace client */
} /* namespace http */
} /* namespace esl */

#endif /* ESL_HTTP_CLIENT_RESPONSEHANDLER_H_ */
