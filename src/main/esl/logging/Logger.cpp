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

#include <esl/logging/Logger.h>
#include <esl/logging/Appender.h>

#include <esl/logging/Interface.h>
#include <esl/Module.h>

namespace esl {
namespace logging {

void setUnblocked(bool isUnblocked) {
	const Interface* interface = esl::getModule().findInterface<Interface>();
	if(interface) {
		interface->setUnblocked(isUnblocked);
	}
}

void setLevel(Level logLevel, const std::string& typeName) {
	const Interface* interface = esl::getModule().findInterface<Interface>();
	if(interface) {
		interface->setLevel(logLevel, typeName);
	}
}

void addAppender(Appender& appender) {
	/* we are done if appender has been already added */
	if(appender.handle != nullptr) {
		return;
	}

	const Interface* interface = esl::getModule().findInterface<Interface>();
	if(interface) {
		appender.handle = interface->addAppender(appender);
	}
}

#if 0
unsigned int getLoggerThreadNo(std::thread::id threadId) {
	esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion());
	const Interface* interface = static_cast<const Interface*>(esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion()));

	if(interface == nullptr) {
		throw esl::addStacktrace(std::runtime_error("no implementation available for \"esl-logging\""));
	}

	return interface->getThreadNo(threadId);
}
#endif

} /* namespace logging */

esl::logging::Logger<> logger("esl");

} /* namespace esl */


