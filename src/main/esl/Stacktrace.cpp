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

#include <esl/Stacktrace.h>
#include <esl/stacktrace/Interface.h>
#include <esl/Module.h>

namespace esl {

namespace {
const char* dummyMessage = "no implementation available for \"esl::Stacktrace\"";

std::unique_ptr<stacktrace::Interface::Stacktrace> createStacktrace(const std::string& implementation, const stacktrace::Interface::Settings& values) {
	const stacktrace::Interface* interface = getModule().findInterface<stacktrace::Interface>(implementation);
	return interface ? interface->createStacktrace(values) : nullptr;
}
} /* anonymous Namespace */

module::Implementation& Stacktrace::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

Stacktrace::Stacktrace(const stacktrace::Interface::Settings& settings, const std::string& implementation)
: stacktrace(createStacktrace(implementation, settings))
{ }
/*
Stacktrace::Stacktrace()
: stacktrace(createStacktrace())
{ }
*/
Stacktrace::Stacktrace(const Stacktrace& aStacktrace)
: stacktrace(aStacktrace.stacktrace ? aStacktrace.stacktrace->clone() : nullptr)
{ }

void Stacktrace::dump(std::ostream& stream) const {
	if(stacktrace) {
		stacktrace->dump(stream);
	}
	else {
		stream << dummyMessage << "\n";
	}
}

void Stacktrace::dump(logging::StreamReal& stream, logging::Location location) const {
	if(stacktrace) {
		stacktrace->dump(stream, location);
	}
	else {
		stream << dummyMessage << "\n";
	}
}

} /* namespace esl */
