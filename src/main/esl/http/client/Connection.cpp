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
#include <esl/object/ValueSettings.h>

namespace esl {
namespace http {
namespace client {

module::Implementation& Connection::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

namespace {
object::ValueSettings settings;
}
Connection::Connection(const utility::URL& hostUrl)
: Interface::Connection(),
  connection(esl::getModule().getInterface<Interface>().createConnection(hostUrl, settings))
{ }

Connection::Connection(const utility::URL& hostUrl,
		std::initializer_list<std::pair<std::string, std::string>> setting,
		const std::string& implementation)
: Interface::Connection(),
  connection(esl::getModule().getInterface<Interface>(implementation).createConnection(hostUrl, object::ValueSettings(std::move(setting))))
{ }

Connection::Connection(const utility::URL& hostUrl,
		const object::Values<std::string>& setting,
		const std::string& implementation)
: Interface::Connection(),
  connection(esl::getModule().getInterface<Interface>(implementation).createConnection(hostUrl, setting))
{ }

Response Connection::send(RequestDynamic& request, ResponseHandler* responseHandler) const {
	return connection->send(request, responseHandler);
}

Response Connection::send(const RequestStatic& request, ResponseHandler* responseHandler) const {
	return connection->send(request, responseHandler);
}

Response Connection::send(const RequestFile& request, ResponseHandler* responseHandler) const {
	return connection->send(request, responseHandler);
}

} /* namespace client */
} /* namespace http */
} /* namespace esl */
