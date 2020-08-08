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

#ifndef ESL_HTTP_CLIENT_REQUEST_H_
#define ESL_HTTP_CLIENT_REQUEST_H_

#include <esl/utility/HttpMethod.h>
#include <esl/http/client/RequestHandler.h>
#include <esl/http/client/Interface.h>

#include <string>
#include <map>
#include <initializer_list>
#include <memory>
#include <functional>

namespace esl {
namespace http {
namespace client {

class Response;
class ResponseHandler;

class Request final {
friend class Interface::Connection;

public:
	Request(std::string path, utility::HttpMethod method,
			ResponseHandler* responseHandler,
			std::unique_ptr<RequestHandler> requestHandler,
			std::initializer_list<std::pair<const std::string, std::string>> requestHeaders = {});
	Request(std::string path, utility::HttpMethod method,
			ResponseHandler* responseHandler,
			std::unique_ptr<RequestHandler> requestHandler,
			std::map<std::string, std::string> requestHeaders);
	Request(const Request&) = delete;
	Request(Request&& other);

	~Request();

	Request& operator=(const Request&) = delete;
	Request& operator=(Request&& other);

	const std::string& getPath() const noexcept;
	const utility::HttpMethod& getMethod() const noexcept;

	RequestHandler* getRequestHandler() const noexcept;
	ResponseHandler* getResponseHandler() const noexcept;

	const std::map<std::string, std::string>& getHeaders() const noexcept;
	void addHeader(const std::string& key, const std::string& value);

private:
	void setResponse(const Response& response);

	std::string path;
	utility::HttpMethod method;

	ResponseHandler* responseHandler = nullptr;

	std::unique_ptr<RequestHandler> requestHandler;
	std::map<std::string, std::string> requestHeaders;
};

} /* namespace client */
} /* namespace http */
} /* namespace esl */

#endif /* ESL_HTTP_CLIENT_REQUEST_H_ */
