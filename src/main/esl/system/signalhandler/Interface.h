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

#ifndef ESL_SYSTEM_SIGNALHANDLER_INTERFACE_H_
#define ESL_SYSTEM_SIGNALHANDLER_INTERFACE_H_

#include <esl/module/Interface.h>
#include <esl/Module.h>
#include <esl/object/Interface.h>
#include <esl/object/Event.h>
#include <esl/utility/Signal.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace esl {
namespace system {
namespace signalhandler {

struct Interface : module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	using SignalHandler = std::unique_ptr<object::Interface::Object>;

	using CreateSignalHandler = SignalHandler (*)(const std::vector<std::pair<std::string, std::string>>& settings, object::Event& event, const utility::Signal& signal);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-system-signalhandler";
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static std::unique_ptr<const module::Interface> createInterface(const char* implementation, CreateSignalHandler createSignalHandler) {
		return std::unique_ptr<const module::Interface>(new Interface(implementation, createSignalHandler));
	}

	Interface(const char* implementation, CreateSignalHandler aCreateSignalHandler)
	: module::Interface(getModule().getId(), getType(), implementation, getModule().getApiVersion()),
	  createSignalHandler(aCreateSignalHandler)
	{ }

	CreateSignalHandler createSignalHandler;
};

} /* namespace signalhandler */
} /* namespace system */
} /* namespace esl */

#endif /* ESL_SYSTEM_SIGNALHANDLER_INTERFACE_H_ */
