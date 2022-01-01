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

#ifndef ESL_COM_BASIC_CLIENT_CONNECTION_H_
#define ESL_COM_BASIC_CLIENT_CONNECTION_H_

#include <esl/com/basic/client/Interface.h>
#include <esl/module/Implementation.h>
#include <esl/io/Output.h>

#include <string>
#include <memory>
#include <utility>
#include <vector>

namespace esl {
namespace com {
namespace basic {
namespace client {

class Connection : public Interface::Connection {
public:
	static module::Implementation& getDefault();

	Connection(const Interface::Settings& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());

	Response send(const Request& request, esl::io::Output output, Interface::CreateInput createInput) const override;
	Response send(const Request& request, esl::io::Output output, esl::io::Input input) const override;

private:
	std::unique_ptr<Interface::ConnectionFactory> connectionFactory;
	std::unique_ptr<Interface::Connection> connection;
};

} /* namespace client */
} /* namespace basic */
} /* namespace com */
} /* namespace esl */

#endif /* ESL_COM_BASIC_CLIENT_CONNECTION_H_ */
