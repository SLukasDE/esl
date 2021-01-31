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

#ifndef ESL_MESSAGING_INTERFACE_H_
#define ESL_MESSAGING_INTERFACE_H_

#include <esl/module/Interface.h>
#include <esl/Module.h>
#include <esl/messaging/messagehandler/Interface.h>
#include <esl/messaging/Consumer.h>
#include <esl/messaging/Producer.h>
#include <esl/messaging/MessageContext.h>
#include <esl/object/Interface.h>
#include <esl/object/Values.h>

#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include <functional>
#include <memory>

namespace esl {
namespace messaging {

struct Interface : esl::module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	//class ProducerFactory : public object::Interface::Object {
	class ProducerFactory : public virtual object::Interface::Object {
	//class ProducerFactory {
	public:
		//virtual ~ProducerFactory() = default;
		virtual std::unique_ptr<Producer> createProducer() = 0;
	};

	public:
	class Client : public object::Interface::Object {
	public:
		using ObjectFactory = std::function<esl::object::Interface::Object*(const MessageContext&)>;

		Client() = default;

		virtual void addObjectFactory(const std::string& id, ObjectFactory objectFactory) = 0;

		virtual Consumer& getConsumer() = 0;

		virtual std::unique_ptr<ProducerFactory> createProducerFactory(const std::string& id, std::vector<std::pair<std::string, std::string>> parameters = {}) = 0;
	};

	using CreateClient = std::unique_ptr<Client> (*)(const std::string& brokers, const object::Values<std::string>& settings);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-messaging";
	}

	static inline const std::string& getApiVersion() {
		return esl::getModule().getApiVersion();
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	Interface(std::string module, std::string implementation,
			CreateClient aCreateClient)
	: esl::module::Interface(std::move(module), getType(), std::move(implementation), getApiVersion()),
	  createClient(aCreateClient)
	{ }

	CreateClient createClient;
};

} /* namespace messaging */
} /* namespace esl */

#endif /* ESL_MESSAGING_INTERFACE_H_ */
