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

#ifndef ESL_COM_BASIC_SERVER_INTERFACE_H_
#define ESL_COM_BASIC_SERVER_INTERFACE_H_

#include <esl/module/Interface.h>
#include <esl/object/Interface.h>
#include <esl/Module.h>
#include <esl/com/basic/server/RequestContext.h>
#include <esl/com/basic/server/requesthandler/Interface.h>

#include <string>
#include <functional>
#include <set>
#include <memory>

namespace esl {
namespace com {
namespace basic {
namespace server {

struct Interface : esl::module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class Socket : public object::Interface::Object {
	public:
		using ObjectFactory = std::function<object::Interface::Object*(const RequestContext&)>;

		virtual ~Socket() = default;

		virtual void addObjectFactory(const std::string& id, ObjectFactory objectFactory) = 0;

		/* this method is non-blocking. A separate thread will be opened to listen */
		virtual void listen(const std::set<std::string>& notifications, requesthandler::Interface::CreateInput createInput) = 0;
		virtual void release() = 0;
		virtual bool wait(std::uint32_t ms) = 0;
	};

	using CreateSocket = std::unique_ptr<Socket> (*)(const Settings& settings);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-com-basic-server";
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static std::unique_ptr<const esl::module::Interface> createInterface(const char* implementation, CreateSocket createSocket) {
		return std::unique_ptr<const esl::module::Interface>(new Interface(implementation, createSocket));
	}

	Interface(const char* implementation, CreateSocket aCreateSocket)
	: esl::module::Interface(esl::getModule().getId(), getType(), implementation, esl::getModule().getApiVersion()),
	  createSocket(aCreateSocket)
	{ }

	CreateSocket createSocket;
};

} /* namespace server */
} /* namespace basic */
} /* namespace com */
} /* namespace esl */

#endif /* ESL_COM_BASIC_SERVER_INTERFACE_H_ */
