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

#ifndef ESL_MESSAGING_SERVER_INTERFACE_H_
#define ESL_MESSAGING_SERVER_INTERFACE_H_

#include <esl/module/Interface.h>
#include <esl/object/Interface.h>
#include <esl/object/Values.h>
#include <esl/Module.h>
#include <esl/messaging/server/MessageContext.h>
#include <esl/messaging/server/messagehandler/Interface.h>

#include <string>
#include <functional>
#include <cstdint>
#include <set>
#include <memory>

namespace esl {
namespace messaging {
namespace server {

struct Interface : esl::module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class Socket {
	public:
		using ObjectFactory = std::function<object::Interface::Object*(const MessageContext&)>;

		virtual ~Socket() = default;

		virtual void addObjectFactory(const std::string& id, ObjectFactory objectFactory) = 0;

		/* this method is non-blocking. A separate thread will be opened to listen */
		virtual void listen(const std::set<std::string>& notifications, messagehandler::Interface::CreateMessageHandler createMessageHandler) = 0;
		virtual void release() = 0;
		virtual bool wait(std::uint32_t ms) = 0;
	};

	using CreateSocket = std::unique_ptr<Socket> (*)(std::uint16_t port, const object::Values<std::string>& settings);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-messaging-server";
	}

	static inline const std::string& getApiVersion() {
		return esl::getModule().getApiVersion();
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	Interface(std::string module, std::string implementation,
			CreateSocket aCreateSocket)
	: esl::module::Interface(std::move(module), getType(), std::move(implementation), getApiVersion()),
	  createSocket(aCreateSocket)
	{ }

	CreateSocket createSocket;
};

} /* namespace server */
} /* namespace messaging */
} /* namespace esl */

#endif /* ESL_MESSAGING_SERVER_INTERFACE_H_ */