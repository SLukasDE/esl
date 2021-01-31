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

#include <esl/messaging/Client.h>
#include <esl/object/ValueSettings.h>
#include <esl/Module.h>

namespace esl {
namespace messaging {

module::Implementation& Client::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

Client::Client(const std::string& brokers,
		std::initializer_list<std::pair<std::string, std::string>> settings,
		const std::string& implementation)
: Interface::Client(),
  client(esl::getModule().getInterface<Interface>(implementation).createClient(brokers, object::ValueSettings(std::move(settings))))
{ }

Client::Client(const std::string& brokers,
		const object::Values<std::string>& settings,
		const std::string& implementation)
: Interface::Client(),
  client(esl::getModule().getInterface<Interface>(implementation).createClient(brokers, settings))
{ }

void Client::addObjectFactory(const std::string& id, ObjectFactory objectFactory) {
	client->addObjectFactory(id, objectFactory);
}

Consumer& Client::getConsumer() {
	return client->getConsumer();
}
/*
std::unique_ptr<Producer> Client::createProducer(const std::string& id, std::vector<std::pair<std::string, std::string>> parameters) {
	return client->createProducer(id, parameters);
}
*/
std::unique_ptr<Interface::ProducerFactory> Client::createProducerFactory(const std::string& id, std::vector<std::pair<std::string, std::string>> parameters) {
	return client->createProducerFactory(id, parameters);
}

} /* namespace messaging */
} /* namespace esl */
