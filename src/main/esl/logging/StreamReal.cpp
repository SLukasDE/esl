/*
MIT License
Copyright (c) 2019, 2020 Sven Lukas

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
#include <esl/logging/Location.h>

#include <esl/logging/Interface.h>
#include <esl/Module.h>

namespace esl {
namespace logging {

StreamReal::StreamReal(const char* typeName, Level ll)
: typeName(typeName),
  level(ll)
{ }

StreamWriter StreamReal::operator()(const void* object) {
    return StreamWriter(getStreamWriter(object, nullptr, nullptr, 0));
}

StreamWriter StreamReal::operator()(const char* function, const char* file, unsigned int lineNo) {
    return StreamWriter(getStreamWriter(nullptr, function, file, lineNo));
}

StreamWriter StreamReal::operator()(const void* object, const char* function, const char* file, unsigned int lineNo) {
    return StreamWriter(getStreamWriter(object, function, file, lineNo));
}

StreamWriter StreamReal::operator<<(std::ostream& (*pf)(std::ostream&)) {
    StreamWriter streamWriter(getStreamWriter(nullptr, nullptr, nullptr, 0));
    streamWriter << pf;
    return streamWriter;
}

bool StreamReal::isEnabled() const {
	const Interface* interface = esl::getModule().getInterfacePointer<Interface>();

	if(interface == nullptr) {
		return false;
	}
	if(enabled == nullptr) {
		enabled = &interface->isEnabled(typeName, level);
	}

	return *enabled;
}

StreamWriter StreamReal::getStreamWriter(const void* object, const char* function, const char* file, unsigned int lineNo) {
	Location location(level, object, typeName, function, file, lineNo, std::this_thread::get_id());
	const Interface* interface = esl::getModule().getInterfacePointer<Interface>();

	if(interface) {
		std::pair<std::ostream&, void*> oStreamAndData = interface->addWriter(location, &enabled);
		return StreamWriter(location, &oStreamAndData.first, oStreamAndData.second);
	}
	return StreamWriter(location, nullptr, nullptr);
}

} /* namespace logging */
} /* namespace esl */




