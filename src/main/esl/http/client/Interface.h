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

#ifndef ESL_HTTP_CLIENT_INTERFACE_H_
#define ESL_HTTP_CLIENT_INTERFACE_H_

#include <esl/module/Interface.h>
#include <esl/Module.h>
#include <string>

namespace esl {
namespace http {
namespace client {

class RequestDynamic;
class RequestStatic;
class RequestFile;
class Response;

struct Interface : esl::module::Interface {
	/* *************************************** *
	 * definitions required for this interface *
	 * *************************************** */
	class Connection {
	public:
		Connection() = default;
		virtual ~Connection() = default;

		void sendGet(Response& response, const RequestDynamic& request) const;
		void sendGet(Response& response, const RequestStatic& request) const;
		void sendGet(Response& response, const RequestFile& request) const;

		void sendPost(Response& response, const RequestDynamic& request) const;
		void sendPost(Response& response, const RequestStatic& request) const;
		void sendPost(Response& response, const RequestFile& request) const;

		void sendPut(Response& response, const RequestDynamic& request) const;
		void sendPut(Response& response, const RequestStatic& request) const;
		void sendPut(Response& response, const RequestFile& request) const;

		void sendDelete(Response& response, const RequestDynamic& request) const;
		void sendDelete(Response& response, const RequestStatic& request) const;
		void sendDelete(Response& response, const RequestFile& request) const;

		virtual void send(Response& response, const RequestDynamic& request, const std::string& method) const = 0;
		virtual void send(Response& response, const RequestStatic& request, const std::string& method) const = 0;
		virtual void send(Response& response, const RequestFile& request, const std::string& method) const = 0;
	};

	using CreateConnection = Connection* (*)(
			const std::string& hostUrl,
            const long timeout,
            const std::string& username,
            const std::string& password,
            const std::string& proxy,
            const std::string& proxyUser,
            const std::string& proxyPassword,
            const std::string& userAgent);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-http-client";
	}

	static inline const std::string& getApiVersion() {
		return esl::getModule().getApiVersion();
	}


	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	Interface(std::string module, std::string implementation,
			CreateConnection aCreateConnection)
	: esl::module::Interface(std::move(module), getType(), std::move(implementation), getApiVersion()),
	  createConnection(aCreateConnection)
	{ }

	static inline void initialize(Interface& interface, CreateConnection createConnection) {
		interface.createConnection = createConnection;
	}

	/* **************************** *
	 * start extension of interface *
	 * **************************** */
	CreateConnection createConnection;
};

} /* namespace client */
} /* namespace http */
} /* namespace esl */

#endif /* ESL_HTTP_CLIENT_INTERFACE_H_ */
