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

#ifndef ESL_MESSAGING_CLIENT_H_
#define ESL_MESSAGING_CLIENT_H_

#include <esl/messaging/Interface.h>
#include <esl/messaging/messagehandler/Interface.h>
#include <esl/messaging/Consumer.h>
#include <esl/messaging/Producer.h>
#include <esl/object/ObjectContext.h>
#include <esl/object/Values.h>
#include <esl/module/Implementation.h>

#include <cstdint>
#include <initializer_list>
#include <utility>
#include <vector>
#include <memory>

namespace esl {
namespace messaging {

class Client final : public Interface::Client {
public:
	static module::Implementation& getDefault();

	Client(const std::string& brokers,
			std::initializer_list<std::pair<std::string, std::string>> settings,
			const std::string& implementation = getDefault().getImplementation());

	Client(const std::string& brokers,
			const object::Values<std::string>& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());

	void addObjectFactory(const std::string& id, ObjectFactory objectFactory) override;

	Consumer& getConsumer() override;
	//std::unique_ptr<Producer> createProducer(const std::string& id, std::vector<std::pair<std::string, std::string>> parameters = {}) override;
	std::unique_ptr<Interface::ProducerFactory> createProducerFactory(const std::string& id, std::vector<std::pair<std::string, std::string>> parameters = {}) override;

private:
	std::unique_ptr<Interface::Client> client;
};

} /* namespace messaging */
} /* namespace esl */

#endif /* ESL_MESSAGING_CLIENT_H_ */
