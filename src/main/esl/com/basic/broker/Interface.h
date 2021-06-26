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

#ifndef ESL_COM_BASIC_BROKER_INTERFACE_H_
#define ESL_COM_BASIC_BROKER_INTERFACE_H_

#include <esl/module/Interface.h>
#include <esl/Module.h>
#include <esl/com/basic/client/Interface.h>
#include <esl/com/basic/server/Interface.h>
#include <esl/object/Interface.h>

#include <string>
#include <utility>
#include <vector>
#include <memory>

namespace esl {
namespace com {
namespace basic {
namespace broker {

struct Interface : esl::module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class Client : public object::Interface::Object {
	public:
		virtual server::Interface::Socket& getSocket() = 0;
		virtual std::unique_ptr<client::Interface::Connection> createConnection(const Settings& parameters) = 0;
	};

	using CreateClient = std::unique_ptr<Client> (*)(const Settings& settings);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-com-basic-broker";
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static std::unique_ptr<const esl::module::Interface> createInterface(const char* implementation, CreateClient createClient) {
		return std::unique_ptr<const esl::module::Interface>(new Interface(implementation, createClient));
	}

	Interface(const char* implementation, CreateClient aCreateClient)
	: esl::module::Interface(esl::getModule().getId(), getType(), implementation, esl::getModule().getApiVersion()),
	  createClient(aCreateClient)
	{ }

	CreateClient createClient;
};

} /* namespace broker */
} /* namespace basic */
} /* namespace com */
} /* namespace esl */

#endif /* ESL_COM_BASIC_BROKER_INTERFACE_H_ */
