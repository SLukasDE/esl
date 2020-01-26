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

#ifndef ESL_LOGGING_INTERFACE_H_
#define ESL_LOGGING_INTERFACE_H_

#include <esl/module/Interface.h>
#include <esl/Module.h>
#include <esl/logging/Location.h>
#include <esl/logging/Level.h>
#include <esl/logging/Appender.h>
#include <ostream>
#include <vector>
#include <functional>


namespace esl {
namespace logging {

class StreamReal;
class Appender;

struct Interface : esl::module::Interface {

	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	using SetUnblocked = void (*)(bool isUnblocked);
	using SetLevel = void (*)(Level logLevel, const std::string& typeName);
	using AddAppender = void(*)(Appender& appender);
	using GetAppenders = std::vector<std::reference_wrapper<Appender>>(*)();
	using IsEnabled = bool& (*)(const char* typeName, Level level);
	using AddWriter = std::pair<std::reference_wrapper<std::ostream>, void*> (*)(const Location& location, bool** enabled);
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

	Interface(std::string module, std::string implementation,
			SetUnblocked aSetUnblocked, SetLevel aSetLevel, AddAppender aAddAppender, GetAppenders aGetAppenders,
			IsEnabled aIsEnabled, AddWriter aAddWriter, RemoveWriter aRemoveWriter, GetThreadNo aGetThreadNo)
	: esl::module::Interface(std::move(module), getId(), std::move(implementation), getApiVersion()),
	  setUnblocked(aSetUnblocked),
	  setLevel(aSetLevel),
	  addAppender(aAddAppender),
	  getAppenders(aGetAppenders),
	  isEnabled(aIsEnabled),
	  addWriter(aAddWriter),
	  removeWriter(aRemoveWriter),
	  getThreadNo(aGetThreadNo)
	{ }

	static void appenderFlushNewLine(Appender& appender, const Location& location, bool enabled) {
		appender.flushNewLine(location, enabled);
	}

	static void appenderWrite(Appender& appender, const Location& location, bool enabled, const char* ptr, std::size_t size) {
		appender.write(location, enabled, ptr, size);
	}

	SetUnblocked setUnblocked;
	SetLevel setLevel;
	AddAppender addAppender;
	GetAppenders getAppenders;
	IsEnabled isEnabled;
	AddWriter addWriter;
	RemoveWriter removeWriter;
	GetThreadNo getThreadNo;
};

} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_INTERFACE_H_ */
