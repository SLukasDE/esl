/*
MIT License
Copyright (c) 2019, 2020 Sven Lukas

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

#ifndef ESL_HTTP_SERVER_INTERFACE_H_
#define ESL_HTTP_SERVER_INTERFACE_H_

#include <esl/module/Interface.h>
#include <esl/object/Interface.h>
#include <esl/object/Values.h>
#include <esl/Module.h>
#include <esl/http/server/RequestContext.h>
#include <esl/http/server/requesthandler/Interface.h>

#include <string>
#include <functional>
#include <cstdint>
#include <vector>
#include <memory>

namespace esl {
namespace http {
namespace server {

struct Interface : esl::module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class Socket {
	public:
		using GetObject = std::function<esl::object::Interface::Object*(const RequestContext&)>;

		Socket() = default;
		virtual ~Socket() = default;

		virtual void addTLSHost(const std::string& hostname, std::vector<unsigned char> certificate, std::vector<unsigned char> key) = 0;
		virtual void setObject(const std::string& id, GetObject getObject) = 0;
		virtual bool listen() = 0;
		virtual void release() = 0;
	};

	using CreateSocket = std::unique_ptr<Socket> (*)(uint16_t port, requesthandler::Interface::CreateRequestHandler createRequestHandler, const object::Values<std::string>& values);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-http-server";
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
} /* namespace http */
} /* namespace esl */

#endif /* ESL_HTTP_SERVER_INTERFACE_H_ */
