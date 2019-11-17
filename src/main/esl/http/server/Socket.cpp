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

#include <esl/http/server/Socket.h>
#include <esl/bootstrap/Interface.h>
#include <esl/Module.h>
#include <esl/Stacktrace.h>

namespace esl {
namespace http {
namespace server {

namespace {

Interface::Socket* createSocket(uint16_t port, uint16_t numThreads, RequestHandlerFactory requestHandlerFactory) {
	const Interface* interface = static_cast<const Interface*>(esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion()));

	if(interface == nullptr) {
		throw esl::addStacktrace(std::runtime_error("no implementation available for \"esl::http::server::Socket\""));
	}

	return interface->createSocket(port, numThreads, requestHandlerFactory);
}

}

Socket::Socket(uint16_t port, uint16_t numThreads, RequestHandlerFactory requestHandlerFactory)
: Interface::Socket(),
  socket(createSocket(port, numThreads, requestHandlerFactory))
{
}

void Socket::addTLSHost(const std::string& hostname, std::vector<unsigned char> certificate, std::vector<unsigned char> key) {
	return socket->addTLSHost(hostname, certificate, key);
}

bool Socket::listen() {
	return socket->listen();
}

void Socket::release() {
	socket->release();
}

} /* namespace server */
} /* namespace http */
} /* namespace esl */
