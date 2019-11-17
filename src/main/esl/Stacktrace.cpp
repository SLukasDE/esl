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

#include <esl/Stacktrace.h>
#include <esl/bootstrap/Interface.h>
#include <esl/Module.h>

namespace esl {

namespace {

bool initialized = false;
const stacktrace::Interface* interface = nullptr;
const char* dummyMessage = "no implementation available for \"esl::Stacktrace\"";

stacktrace::Interface::Stacktrace* createStacktrace() {
	if(initialized == false) {
		initialized = true;
		interface = static_cast<const stacktrace::Interface*>(esl::getModule().getInterface(stacktrace::Interface::getId(), stacktrace::Interface::getApiVersion()));

		if(interface == nullptr) {
			throw esl::addStacktrace(std::runtime_error(dummyMessage));
		}
	}

	if(interface == nullptr) {
		return nullptr;
	}

	return interface->createStacktrace();
}

} /* anonymous Namespace */


//logging::Logger Stacktrace::logger("esl::Stacktrace");

Stacktrace::Stacktrace()
: stacktrace(createStacktrace()) {
}

Stacktrace::Stacktrace(const esl::Stacktrace& aStacktrace)
: stacktrace(aStacktrace.stacktrace ? aStacktrace.stacktrace->clone() : nullptr) {
}

void Stacktrace::allowDummy() {
	if(initialized == false && interface == nullptr) {
		interface = static_cast<const stacktrace::Interface*>(esl::getModule().getInterface(stacktrace::Interface::getId(), stacktrace::Interface::getApiVersion()));
	}
	initialized = true;
}

void Stacktrace::dump(std::ostream& oStream) const {
	if(stacktrace) {
		stacktrace->dump(oStream);
	}
	else {
		oStream << dummyMessage << "\n";
	}
}
/*
void Stacktrace::dump(logging::Level level) const {
	dump(logger, level);
}
*/
void Stacktrace::dump(logging::Logger& logger, logging::Level level) const {
	if(stacktrace) {
		stacktrace->dump(logger, level);
	}
	else {
		switch(level) {
		case esl::logging::Level::TRACE:
			logger.trace << dummyMessage << "\n";
			break;
		case esl::logging::Level::DEBUG:
			logger.debug << dummyMessage << "\n";
			break;
		case esl::logging::Level::INFO:
			logger.info << dummyMessage << "\n";
			break;
		case esl::logging::Level::WARN:
			logger.warn << dummyMessage << "\n";
			break;
		case esl::logging::Level::ERROR:
			logger.error << dummyMessage << "\n";
			break;
		default: /* logging::Level::SILENT */
			break;
		}
	}
}

} /* namespace esl */
