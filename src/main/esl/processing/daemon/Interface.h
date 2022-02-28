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
#if 0
#ifndef ESL_PROCESSING_DAEMON_INTERFACE_H_
#define ESL_PROCESSING_DAEMON_INTERFACE_H_

#include <esl/module/Interface.h>
#include <esl/object/Interface.h>
#include <esl/Module.h>

#include <string>
#include <functional>
#include <cstdint>
#include <memory>

namespace esl {
namespace processing {
namespace daemon {

struct Interface : esl::module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class Daemon : public object::Interface::Object {
	public:
		/* this methods are non-blocking. A separate thread will be created */
		virtual bool start(std::function<void()> onReleasedHandler) = 0;
		virtual void release() = 0;
		virtual bool wait(std::uint32_t ms) = 0;
	};

	using CreateDaemon = std::unique_ptr<Daemon> (*)(const Settings& settings);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-processing-daemon";
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static std::unique_ptr<const esl::module::Interface> createInterface(const char* implementation, CreateDaemon createDaemon) {
		return std::unique_ptr<const esl::module::Interface>(new Interface(implementation, createDaemon));
	}

	Interface(const char* implementation, CreateDaemon aCreateDaemon)
	: esl::module::Interface(esl::getModule().getId(), getType(), implementation, esl::getModule().getApiVersion()),
	  createDaemon(aCreateDaemon)
	{ }

	CreateDaemon createDaemon;
};

} /* namespace daemon */
} /* namespace processing */
} /* namespace esl */

#endif /* ESL_PROCESSING_DAEMON_INTERFACE_H_ */
#endif
