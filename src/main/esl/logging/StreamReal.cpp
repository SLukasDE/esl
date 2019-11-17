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

#include <esl/logging/StreamReal.h>
//#include <esl/logging/Logger.h>
#include <esl/logging/Id.h>

#include <esl/logging/Interface.h>
#include <esl/bootstrap/Interface.h>
#include <esl/Module.h>
#include <esl/Stacktrace.h>

namespace esl {
namespace logging {

namespace {

std::pair<std::reference_wrapper<std::ostream>, void*> addWriter(Id id, bool** enabled) {
	esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion());
	const Interface* interface = static_cast<const Interface*>(esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion()));

	if(interface == nullptr) {
		throw esl::addStacktrace(std::runtime_error("no implementation available for \"esl-logging\""));
	}

	return interface->addWriter(id, enabled);
}

}

StreamReal::StreamReal(const char* typeName, Level ll)
: typeName(typeName),
  level(ll)
{ }

StreamWriter StreamReal::operator()(void* object) {
    return StreamWriter(getStreamWriter(object, nullptr, nullptr, 0));
}

StreamWriter StreamReal::operator<<(std::ostream& (*pf)(std::ostream&)) {
    StreamWriter streamWriter(getStreamWriter(nullptr, nullptr, nullptr, 0));
    streamWriter << pf;
    return streamWriter;
}

StreamWriter StreamReal::operator()(const char* function, const char* file, unsigned int lineNo) {
    return StreamWriter(getStreamWriter(nullptr, function, file, lineNo));
}

StreamWriter StreamReal::operator()(void* object, const char* function, const char* file, unsigned int lineNo) {
    return StreamWriter(getStreamWriter(object, function, file, lineNo));
}

StreamWriter StreamReal::getStreamWriter(void* object, const char* function, const char* file, unsigned int lineNo) {
	Id id(level, object, typeName, function, file, lineNo, std::this_thread::get_id());
	std::pair<std::ostream&, void*> oStreamAndData = addWriter(id, &enabled);
	return StreamWriter(id, oStreamAndData.first, oStreamAndData.second);
}

} /* namespace logging */
} /* namespace esl */




