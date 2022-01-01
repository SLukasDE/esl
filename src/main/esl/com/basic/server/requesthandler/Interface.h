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

#ifndef ESL_COM_BASIC_SERVER_REQUESTHANDLER_INTERFACE_H_
#define ESL_COM_BASIC_SERVER_REQUESTHANDLER_INTERFACE_H_

#include <esl/io/Input.h>
#include <esl/com/basic/server/RequestContext.h>
#include <esl/object/Interface.h>
#include <esl/module/Interface.h>
#include <esl/Module.h>

#include <string>
#include <set>
#include <memory>


namespace esl {
namespace com {
namespace basic {
namespace server {
namespace requesthandler {

struct Interface : esl::module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class RequestHandler : public object::Interface::Object {
	public:
		virtual io::Input accept(RequestContext&, object::Interface::ObjectContext&) const = 0;

		/* Tells server what kind of messages MUST NOT be filtered.
		 * Method 'accept' is called AT LEAST for messages that match this kind.
		 * Be aware about that accept MIGHT BE called for other messages as well.
		 * So, it is important to check the 'kind' of message in method 'accept'.
		 */
		virtual std::set<std::string> getNotifiers() const = 0;
	};

	using CreateRequestHandler = std::unique_ptr<RequestHandler> (*)(const module::Interface::Settings& settings);

	//using CreateInput = io::Input (*)(RequestContext&, object::Interface::ObjectContext&);
	//using GetNotifiers = const std::set<std::string>& (*)(const object::Interface::Object*);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-com-basic-server-requesthandler";
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static std::unique_ptr<const esl::module::Interface> createInterface(const char* implementation, CreateRequestHandler createRequestHandler) {
		return std::unique_ptr<const esl::module::Interface>(new Interface(implementation, createRequestHandler));
	}

	Interface(const char* implementation, CreateRequestHandler aCreateRequestHandler)
	: esl::module::Interface(esl::getModule().getId(), getType(), implementation, esl::getModule().getApiVersion()),
	  createRequestHandler(aCreateRequestHandler)
	{ }

	CreateRequestHandler createRequestHandler;
};

} /* namespace requesthandler */
} /* namespace server */
} /* namespace basic */
} /* namespace com */
} /* namespace esl */

#endif /* ESL_COM_BASIC_SERVER_REQUESTHANDLER_INTERFACE_H_ */
