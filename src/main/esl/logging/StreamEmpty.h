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

#ifndef ESL_LOGGING_STREAMEMPTY_H_
#define ESL_LOGGING_STREAMEMPTY_H_

#include <ostream>
#include <esl/logging/Level.h>

namespace esl {
namespace logging {

class StreamEmpty {
public:
	StreamEmpty() = default;
	inline StreamEmpty(const char*, Level) { };

    inline StreamEmpty& operator()(const void*) {
		return *this;
    }
    inline StreamEmpty& operator()(const char*, const char*, unsigned int) {
		return *this;
    }
    inline StreamEmpty& operator()(const void*, const char*, const char*, unsigned int) {
		return *this;
    }

	template<typename T>
	inline StreamEmpty& operator<<(const T& t) {
		return *this;
	}

    inline StreamEmpty& operator<<(std::ostream& (*pf)(std::ostream&)) {
    	return *this;
    }

	inline constexpr bool isEnabled() const {
		return false;
	}
};

} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_STREAMEMPTY_H_ */
