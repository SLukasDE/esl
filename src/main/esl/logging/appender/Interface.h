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

#ifndef ESL_LOGGING_APPENDER_INTERFACE_H_
#define ESL_LOGGING_APPENDER_INTERFACE_H_

#include <esl/module/Interface.h>
#include <esl/object/Interface.h>
#include <esl/Module.h>
#include <esl/logging/Location.h>
#include <esl/logging/layout/Interface.h>

#include <string> // std::size_t
#include <ostream>
#include <memory>

namespace esl {
namespace logging {
class Interface;
namespace appender {

struct Interface : module::Interface {

	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class Appender : public object::Interface::Object {
	public:
		enum class RecordLevel {
			ALL, SELECTED, OFF
		};

		~Appender();

		virtual void setLayout(const layout::Interface::Layout* aLayout) = 0;
		virtual const layout::Interface::Layout* getLayout() const = 0;

		/* both methods are NOT thread-safe */
		virtual void setRecordLevel(RecordLevel aRecordLevel = RecordLevel::SELECTED) = 0;
		virtual RecordLevel getRecordLevel() const = 0;

		virtual void flush() = 0;
		virtual void flush(std::ostream& oStream) = 0;
		virtual void write(const Location& location, const char* ptr, std::size_t size) = 0;

	//private:
		void* handle = nullptr;
	};

	using CreateAppender = std::unique_ptr<Appender> (*)(const Settings& settings);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-logging-appender";
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static std::unique_ptr<const module::Interface> createInterface(const char* implementation, CreateAppender createAppender) {
		return std::unique_ptr<const module::Interface>(new Interface(implementation, createAppender));
	}

	Interface(const char* implementation, CreateAppender aCreateAppender)
	: module::Interface(getModule().getId(), getType(), implementation, getModule().getApiVersion()),
	  createAppender(aCreateAppender)
	{ }

	CreateAppender createAppender;
};

} /* namespace appender */
} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_APPENDER_INTERFACE_H_ */
