/*
MIT License
Copyright (c) 2019 Sven Lukas

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

#ifndef ESL_STACKTRACE_INTERFACE_H_
#define ESL_STACKTRACE_INTERFACE_H_

#include <esl/bootstrap/Interface.h>
#include <esl/Module.h>
#include <esl/logging/Level.h>
#include <esl/logging/Logger.h>
#include <ostream>
#include <memory>

namespace esl {
namespace stacktrace {

struct Interface : esl::bootstrap::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class Stacktrace {
	public:
		Stacktrace() = default;
		virtual ~Stacktrace() = default;

		virtual void dump(std::ostream& oStream) const = 0;
		virtual void dump(logging::Logger& logger, logging::Level level = logging::Level::ERROR) const = 0;
		virtual std::unique_ptr<Stacktrace> clone() const = 0;
	};

	using CreateStacktrace = Stacktrace* (*)();

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getId() {
		return "esl-stacktrace";
	}
	static inline const std::string& getApiVersion() {
		return esl::getModule().getApiVersion();
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static inline void initialize(Interface& interface, CreateStacktrace createStacktrace) {
		interface.next = nullptr;
		interface.id = getId();
		interface.apiVersion = getApiVersion();
		interface.createStacktrace = createStacktrace;
	}

	CreateStacktrace createStacktrace;
};

} /* namespace stacktrace */
} /* namespace esl */

#endif /* ESL_STACKTRACE_INTERFACE_H_ */
