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

#include <esl/com/basic/client/Connection.h>
#include <esl/object/Properties.h>
#include <esl/logging/Logger.h>
#include <esl/Module.h>

namespace esl {
namespace com {
namespace basic {
namespace client {

namespace {
esl::logging::Logger<> logger("esl::com::basic::client::Connection");
}

module::Implementation& Connection::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

Connection::Connection(const Interface::Settings& settings, const std::string& implementation)
: connectionFactory(esl::getModule().getInterface<Interface>(implementation).createConnectionFactory(settings)),
  connection(connectionFactory->createConnection())
{
	logger.warn << "*****************************************************************************************\n";
	logger.warn << "*** esl::com::basic::client::Connection is DEPRECATED! Don't use this class anymore ! ***\n";
	logger.warn << "***  Use esl::com::basic::client::ConnectionFactory instead to create a connection !  ***\n";
	logger.warn << "*****************************************************************************************\n";
}

Response Connection::send(const Request& request, esl::io::Output output, Interface::CreateInput createInput) const {
	return connection->send(request, std::move(output), createInput);
}

Response Connection::send(const Request& request, esl::io::Output output, esl::io::Input input) const {
	return connection->send(request, std::move(output), std::move(input));
}

} /* namespace client */
} /* namespace basic */
} /* namespace com */
} /* namespace esl */
