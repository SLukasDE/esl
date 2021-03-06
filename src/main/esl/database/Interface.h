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

#ifndef ESL_DATABASE_INTERFACE_H_
#define ESL_DATABASE_INTERFACE_H_

#include <esl/module/Interface.h>
#include <esl/Module.h>
#include <esl/object/Interface.h>
#include <esl/database/Connection.h>

#include <string>
#include <functional>
#include <cstdint>
#include <vector>
#include <memory>

namespace esl {
namespace database {

struct Interface : esl::module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class ConnectionFactory : public esl::object::Interface::Object {
	public:
	    virtual std::unique_ptr<Connection> createConnection() = 0;
	};

	using CreateConnectionFactory = std::unique_ptr<ConnectionFactory>(*)(const Settings& settings);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-database";
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static std::unique_ptr<const esl::module::Interface> createInterface(const char* implementation, CreateConnectionFactory createConnectionFactory) {
		return std::unique_ptr<const esl::module::Interface>(new Interface(implementation, createConnectionFactory));
	}

	Interface(const char* implementation, CreateConnectionFactory aCreateConnectionFactory)
	: esl::module::Interface(esl::getModule().getId(), getType(), implementation, esl::getModule().getApiVersion()),
	  createConnectionFactory(aCreateConnectionFactory)
	{ }

	CreateConnectionFactory createConnectionFactory;
};

} /* namespace database */
} /* namespace esl */

#endif /* ESL_DATABASE_INTERFACE_H_ */
