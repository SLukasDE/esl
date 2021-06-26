/*
MIT License
Copyright (c) 2021 Sven Lukas

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

#ifndef ESL_COM_BASIC_SERVER_SOCKET_H_
#define ESL_COM_BASIC_SERVER_SOCKET_H_

#include <esl/com/basic/server/Interface.h>
#include <esl/com/basic/server/requesthandler/Interface.h>
#include <esl/module/Implementation.h>

#include <memory>

namespace esl {
namespace com {
namespace basic {
namespace server {

class Socket final : public Interface::Socket {
public:
	static module::Implementation& getDefault();

	Socket(const Interface::Settings& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());

	void addObjectFactory(const std::string& id, ObjectFactory objectFactory) override;

	void listen(const std::set<std::string>& notifications, requesthandler::Interface::CreateInput createInput) override;
	void release() override;
	bool wait(std::uint32_t ms) override;

private:
	std::unique_ptr<Interface::Socket> socket;
};

} /* namespace server */
} /* namespace basic */
} /* namespace com */
} /* namespace esl */

#endif /* ESL_COM_BASIC_SERVER_SOCKET_H_ */
