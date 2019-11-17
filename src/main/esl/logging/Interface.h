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

#ifndef ESL_LOGGING_INTERFACE_H_
#define ESL_LOGGING_INTERFACE_H_

#include <esl/bootstrap/Interface.h>
#include <esl/Module.h>
#include <esl/logging/Id.h>
#include <esl/logging/Appender.h>
#include <ostream>
#include <vector>
#include <functional>


namespace esl {
namespace logging {

class StreamReal;
class Appender;

struct Interface : esl::bootstrap::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	using SetUnblocked = void (*)(bool isUnblocked);
	using SetLevel = void (*)(Level logLevel, const std::string& typeName);
	using AddAppender = void(*)(Appender& appender);
	using GetAppenders = std::vector<std::reference_wrapper<Appender>>(*)();
	using AddWriter = std::pair<std::reference_wrapper<std::ostream>, void*> (*)(Id id, bool** enabled);
	using RemoveWriter = void (*)(std::ostream& ostream, void* data);
	using GetThreadNo = unsigned int (*)(std::thread::id threadId);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getId() {
		return "esl-logging";
	}
	static inline const std::string& getApiVersion() {
		return esl::getModule().getApiVersion();
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static inline void initialize(Interface& interface, SetUnblocked setUnblocked, SetLevel setLevel, AddAppender addAppender, GetAppenders getAppenders, AddWriter addWriter, RemoveWriter removeWriter, GetThreadNo getThreadNo) {
		interface.next = nullptr;
		interface.id = getId();
		interface.apiVersion = getApiVersion();
		interface.setUnblocked = setUnblocked;
		interface.setLevel = setLevel;
		interface.addAppender = addAppender;
		interface.getAppenders = getAppenders;
		interface.addWriter = addWriter;
		interface.removeWriter = removeWriter;
		interface.getThreadNo = getThreadNo;
	}

	static void appenderFlushNewLine(Appender& appender, const Id& id, bool enabled) {
		appender.flushNewLine(id, enabled);
	}
	static void appenderWrite(Appender& appender, const Id& id, bool enabled, const char* ptr, std::size_t size) {
		appender.write(id, enabled, ptr, size);
	}

	SetUnblocked setUnblocked;
	SetLevel setLevel;
//	AppenderFlushNewLine appenderFlushNewLine;
//	AppenderWrite appenderWrite;
	AddAppender addAppender;
	GetAppenders getAppenders;
	AddWriter addWriter;
	RemoveWriter removeWriter;
	GetThreadNo getThreadNo;
};

} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_INTERFACE_H_ */
