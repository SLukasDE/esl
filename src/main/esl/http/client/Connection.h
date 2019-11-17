/*
MIT License
Copyright (c) 2019 Sven Lukas

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

#ifndef SRC_MAIN_C___ESL_SERVICE_CLIENT_CONNECTION_H_
#define SRC_MAIN_C___ESL_SERVICE_CLIENT_CONNECTION_H_

#include <esl/http/client/Interface.h>
//#include <esl/http/client/Request.h>
//#include <esl/http/client/Response.h>
#include <string>
#include <memory>

namespace esl {
namespace http {
namespace client {

class Connection : public Interface::Connection {
public:
	Connection(const std::string& hostUrl,
               const long timeout,
               const std::string& username = "",
               const std::string& password = "",
               const std::string& proxy = "",
			   const std::string& proxyUser = "",
			   const std::string& proxyPassword = "",
               const std::string& userAgent = "esl-http-client");

	void send(Response& response, const RequestDynamic& request, const std::string& method) const;
	void send(Response& response, const RequestStatic& request, const std::string& method) const;
	void send(Response& response, const RequestFile& request, const std::string& method) const;

private:
	std::unique_ptr<Interface::Connection> connection;
};

} /* namespace client */
} /* namespace http */
} /* namespace esl */

#endif /* SRC_MAIN_C___ESL_SERVICE_CLIENT_CONNECTION_H_ */
