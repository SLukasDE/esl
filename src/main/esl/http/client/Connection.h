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

#ifndef SRC_MAIN_C___ESL_SERVICE_CLIENT_CONNECTION_H_
#define SRC_MAIN_C___ESL_SERVICE_CLIENT_CONNECTION_H_

#include <esl/http/client/Interface.h>
#include <esl/http/client/RequestDynamic.h>
#include <esl/http/client/RequestStatic.h>
#include <esl/http/client/RequestFile.h>
#include <esl/http/client/Response.h>
#include <esl/http/client/ResponseHandler.h>
#include <esl/object/Values.h>
#include <esl/utility/URL.h>

#include <string>
#include <initializer_list>
#include <memory>

namespace esl {
namespace http {
namespace client {

class Connection : public Interface::Connection {
public:
	Connection(const utility::URL& hostUrl, std::initializer_list<std::pair<std::string, std::string>> values,
			   const std::string& implementation = getDefaultImplementation());

	Connection(const utility::URL& hostUrl, const object::Values<std::string>& values,
			   const std::string& implementation = getDefaultImplementation());

	Response send(RequestDynamic& request, ResponseHandler* responseHandler = nullptr) const override;
	Response send(const RequestStatic& request, ResponseHandler* responseHandler = nullptr) const override;
	Response send(const RequestFile& request, ResponseHandler* responseHandler = nullptr) const override;

	static void setDefaultImplementation(std::string implementation);
	static const std::string& getDefaultImplementation();

private:
	std::unique_ptr<Interface::Connection> connection;
};

} /* namespace client */
} /* namespace http */
} /* namespace esl */

#endif /* SRC_MAIN_C___ESL_SERVICE_CLIENT_CONNECTION_H_ */
