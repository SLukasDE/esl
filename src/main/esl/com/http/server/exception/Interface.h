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

#ifndef ESL_COM_HTTP_SERVER_EXCEPTION_INTERFACE_H_
#define ESL_COM_HTTP_SERVER_EXCEPTION_INTERFACE_H_

#include <esl/module/Interface.h>
#include <esl/Module.h>
#include <esl/utility/MIME.h>
#include <esl/Stacktrace.h>

#include <string>
#include <memory>
#include <exception>

namespace esl {
namespace com {
namespace http {
namespace server {
namespace exception {

struct Interface : esl::module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	struct Message final {
		unsigned short statusCode = 500;
		esl::utility::MIME contentType = esl::utility::MIME::textHtml;

		std::string title;
		std::string message;
		std::string details;

		std::unique_ptr<esl::Stacktrace> stacktrace;
	};

	using CreateMessage = std::unique_ptr<Message> (*)(const std::exception& e);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-com-http-server-exception-message";
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static std::unique_ptr<const esl::module::Interface> createInterface(const char* implementation, CreateMessage createMessage) {
		return std::unique_ptr<const esl::module::Interface>(new Interface(implementation, createMessage));
	}

	Interface(const char* implementation, CreateMessage aCreateMessage)
	: esl::module::Interface(esl::getModule().getId(), getType(), implementation, esl::getModule().getApiVersion()),
	  createMessage(aCreateMessage)
	{ }

	CreateMessage createMessage;
};

} /* namespace exception */
} /* namespace server */
} /* namespace http */
} /* namespace com */
} /* namespace esl */

#endif /* ESL_COM_HTTP_SERVER_EXCEPTION_INTERFACE_H_ */
