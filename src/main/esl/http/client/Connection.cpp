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

#include <esl/http/client/Connection.h>
#include <esl/http/client/Interface.h>
#include <esl/Module.h>

namespace esl {
namespace http {
namespace client {

Connection::Connection(const std::string& hostUrl, const long timeout,
        const std::string& username,
        const std::string& password,
        const std::string& proxy,
        const std::string& proxyUser,
        const std::string& proxyPassword,
        const std::string& userAgent)
: Interface::Connection(),
  connection(esl::getModule().getInterface<Interface>().createConnection(hostUrl, timeout, username, password, proxy, proxyUser, proxyPassword, userAgent))
{
}

void Connection::send(Response &response, const RequestDynamic& request, const std::string& method) const {
	return connection->send(response, request, method);
}

void Connection::send(Response &response, const RequestStatic& request, const std::string& method) const {
	return connection->send(response, request, method);
}

void Connection::send(Response &response, const RequestFile& request, const std::string& method) const {
	return connection->send(response, request, method);
}

} /* namespace client */
} /* namespace http */
} /* namespace esl */
