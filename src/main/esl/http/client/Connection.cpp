/*
MIT License
Copyright (c) 2019-2021 Sven Lukas

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
#include <esl/object/ValueSettings.h>
#include <esl/logging/Logger.h>
#include <esl/Module.h>

namespace esl {
namespace http {
namespace client {

namespace {
esl::logging::Logger<> logger("esl::http::client::Connection");
}

module::Implementation& Connection::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

Connection::Connection(const utility::URL& hostUrl,
		std::initializer_list<std::pair<std::string, std::string>> setting,
		const std::string& implementation)
: Interface::Connection(),
  connection(esl::getModule().getInterface<Interface>(implementation).createConnection(hostUrl, object::ValueSettings(std::move(setting))))
{ }

Connection::Connection(const utility::URL& hostUrl,
		const object::Values<std::string>& settings,
		const std::string& implementation)
: Interface::Connection(),
  connection(esl::getModule().getInterface<Interface>(implementation).createConnection(hostUrl, settings))
{ }

PreparedRequest Connection::prepare(Request&& request) const {
	return connection->prepare(std::move(request));
}

PreparedRequest Connection::prepare(const Request& request) const {
	return connection->prepare(request);
}
/*
Response Connection::send(Request request) const {
	Data data;
    return send(std::move(request), data);
}

Response Connection::send(Request&& request, Data& data) const {
	return connection->send(std::move(request), data);
}

void Connection::addArguments(Data& data, Input&& input) {
	data.input = std::move(input);
}

void Connection::addArguments(Data& data, utility::io::Output&& output) {
	data.output = std::move(output);
}
*/
} /* namespace client */
} /* namespace http */
} /* namespace esl */
