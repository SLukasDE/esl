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

#ifndef ESL_COM_HTTP_SERVER_SOCKET_H_
#define ESL_COM_HTTP_SERVER_SOCKET_H_

#include <esl/com/http/server/Interface.h>
#include <esl/com/http/server/requesthandler/Interface.h>
#include <esl/object/Interface.h>
#include <esl/module/Implementation.h>

#include <utility>
#include <functional>
#include <string>
#include <cstdint>
#include <memory>

namespace esl {
namespace com {
namespace http {
namespace server {

class Socket final : public Interface::Socket {
public:
	static module::Implementation& getDefault();

	Socket(const Interface::Settings& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());

	void addTLSHost(const std::string& hostname, std::vector<unsigned char> certificate, std::vector<unsigned char> key) override;

	void listen(const requesthandler::Interface::RequestHandler& requestHandler, std::function<void()> onReleasedHandler) override;
	void release() override;
	bool wait(std::uint32_t ms) override;

private:
	std::unique_ptr<Interface::Socket> socket;
};

} /* namespace server */
} /* namespace http */
} /* namespace com */
} /* namespace esl */

#endif /* ESL_COM_HTTP_SERVER_SOCKET_H_ */
