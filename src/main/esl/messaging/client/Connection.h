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

#ifndef ESL_MESSAGING_CLIENT_CONNECTION_H_
#define ESL_MESSAGING_CLIENT_CONNECTION_H_

#include <esl/messaging/client/Interface.h>
#include <esl/module/Implementation.h>
#include <esl/object/Values.h>
#include <esl/io/Output.h>

#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <initializer_list>

namespace esl {
namespace messaging {
namespace client {

class Connection : public Interface::Connection {
public:
	static module::Implementation& getDefault();

	Connection(std::initializer_list<std::pair<std::string, std::string>> settings,
			const std::string& implementation = getDefault().getImplementation());

	Connection(const object::Values<std::string>& settings = getDefault().getProperties(),
			const std::string& implementation = getDefault().getImplementation());

	io::Output sendMessage(io::Output output, std::vector<std::pair<std::string, std::string>> parameters) override;

private:
	std::unique_ptr<Interface::Connection> connection;
};

} /* namespace client */
} /* namespace messaging */
} /* namespace esl */

#endif /* ESL_MESSAGING_CLIENT_CONNECTION_H_ */
