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

#ifndef ESL_LOGGING_APPENDER_H_
#define ESL_LOGGING_APPENDER_H_

#include <esl/logging/Logger.h>
#include <esl/logging/Id.h>
#include <esl/logging/Layout.h>
#include <cstddef>

namespace esl {
namespace logging {

class Logger;
class Interface;

class Appender {
friend class Logger;
friend class Interface;
public:
	enum class RecordLevel {
		ALL, SELECTED, OFF
	};

	Appender() = default;
	virtual ~Appender() = default;

	inline Layout& getLayout() {
		return layout;
	}

	/* method is NOT thread-safe */
	inline RecordLevel getRecordLevel() const {
		return recordLevel;
	}

	/* method is NOT thread-safe */
	inline void setRecordLevel(RecordLevel recordLevel = RecordLevel::SELECTED) {
		this->recordLevel = recordLevel;
	}

protected:
	virtual void flushNewLine(const Id& id, bool enabled) = 0;
	virtual void write(const Id& id, bool enabled, const char* ptr, std::size_t size) = 0;

private:
	Layout layout;
	RecordLevel recordLevel = RecordLevel::SELECTED;
};

} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_APPENDER_H_ */
