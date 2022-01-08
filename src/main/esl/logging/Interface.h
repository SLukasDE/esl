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

#ifndef ESL_LOGGING_INTERFACE_H_
#define ESL_LOGGING_INTERFACE_H_

#include <esl/module/Interface.h>
#include <esl/Module.h>
#include <esl/logging/Location.h>
#include <esl/logging/Level.h>
#include <esl/logging/appender/Interface.h>
#include <esl/logging/OStream.h>

#include <ostream>
#include <vector>
#include <functional>
#include <memory>

namespace esl {
namespace logging {

struct Interface : esl::module::Interface {

	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	using SetUnblocked = void (*)(bool isUnblocked);
	using SetLevel = void (*)(Level logLevel, const std::string& typeName);
	using AddAppender = void*(*)(appender::Interface::Appender& appender);
	using RemoveAppender = void(*)(void* handle);
	using IsEnabled = bool (*)(const char* typeName, Level level);
	using CreateOStream = std::unique_ptr<OStream> (*)(const Location& location);
	using GetThreadNo = unsigned int (*)(std::thread::id threadId);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-logging";
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static std::unique_ptr<const esl::module::Interface> createInterface(const char* implementation,
			SetUnblocked setUnblocked, SetLevel setLevel, AddAppender addAppender, RemoveAppender removeAppender,
			IsEnabled isEnabled, CreateOStream createOStream, GetThreadNo getThreadNo) {
		return std::unique_ptr<const esl::module::Interface>(new Interface(implementation,
				setUnblocked, setLevel, addAppender, removeAppender, isEnabled, createOStream, getThreadNo));
	}

	Interface(const char* implementation,
			SetUnblocked aSetUnblocked, SetLevel aSetLevel, AddAppender aAddAppender, RemoveAppender aRemoveAppender,
			IsEnabled aIsEnabled, CreateOStream aCreateOStream, GetThreadNo aGetThreadNo)
	: esl::module::Interface(esl::getModule().getId(), getType(), implementation, esl::getModule().getApiVersion()),
	  setUnblocked(aSetUnblocked),
	  setLevel(aSetLevel),
	  addAppender(aAddAppender),
	  removeAppender(aRemoveAppender),
	  isEnabled(aIsEnabled),
	  createOStream(aCreateOStream),
	  getThreadNo(aGetThreadNo)
	{ }

	static void appenderFlush(appender::Interface::Appender& appender) {
		appender.flush();
	}

	static void appenderWrite(appender::Interface::Appender& appender, const Location& location, const char* ptr, std::size_t size) {
		appender.write(location, ptr, size);
	}

	SetUnblocked setUnblocked;
	SetLevel setLevel;
	AddAppender addAppender;
	RemoveAppender removeAppender;
	IsEnabled isEnabled;
	CreateOStream createOStream;
	GetThreadNo getThreadNo;
};

} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_INTERFACE_H_ */
