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

#ifndef ESL_LOGGING_LOCATION_H_
#define ESL_LOGGING_LOCATION_H_

#include <esl/logging/Level.h>
#include <thread>
#include <cstring>
#include <ctime>

namespace esl {
namespace logging {

struct Location {
	Location() = default;

	Location(Level level, const void* object, const char* typeName, const char* function, const char* file, std::size_t line, std::thread::id threadId)
	: level(level),
	  object(object),
	  typeName(typeName),
	  function(function),
	  file(file),
	  line(line),
	  threadId(threadId)
	{ }

	inline static int stringCmp(const char* s1, const char* s2) {
		if(s1 == nullptr) {
			return s2 == nullptr ? 0 : -1;
		}
		if(s2 == nullptr) {
			return 1;
		}
		return std::strcmp(s1, s2);
	}
	inline static int stringEqual(const char* s1, const char* s2) {
		return stringCmp(s1, s2) == 0;
	}

	inline bool operator==(const Location& location) const {
		return timestamp == location.timestamp &&
				level == location.level &&
				object == location.object &&
				stringEqual(typeName, location.typeName) &&
				stringEqual(function, location.function) &&
				stringEqual(file, location.file) &&
				line == location.line &&
				threadId == location.threadId;
	}

	inline bool operator!=(const Location& location) const {
		return !(*this == location);
	}

	std::time_t timestamp = std::time(nullptr);
	Level level = Level::SILENT;
	const void* object = nullptr;
	const char* typeName = nullptr;
	const char* function = nullptr;
	const char* file = nullptr;
	std::size_t line = 0;
	std::thread::id threadId = std::this_thread::get_id();

	// this is just an additional payload and has no effect to constructor, comperator etc.
	bool enabled = true;
};

} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_LOCATION_H_ */
