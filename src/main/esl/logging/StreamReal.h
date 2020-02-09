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

#ifndef ESL_LOGGING_STREAMREAL_H_
#define ESL_LOGGING_STREAMREAL_H_

#include <esl/logging/Level.h>
#include <esl/logging/StreamWriter.h>

namespace esl {
namespace logging {

class StreamReal {
public:
	StreamReal(const char* typeName, Level ll);
	~StreamReal() = default;

    StreamWriter operator()(const void* object);
    StreamWriter operator()(const char* function, const char* file, unsigned int lineNo);
    StreamWriter operator()(const void* object, const char* function, const char* file, unsigned int lineNo);

	template<typename T>
	inline StreamWriter operator<<(const T& t) {
        StreamWriter streamWriter(getStreamWriter(nullptr, nullptr, nullptr, 0));
        streamWriter << t;
        return streamWriter;
	}

    StreamWriter operator<<(std::ostream& (*pf)(std::ostream&));

    const char* getTypeName() const {
    	return typeName;
    }

	Level getLevel() const {
		return level;
	}

	bool isEnabled() const;

private:
    StreamWriter getStreamWriter(const void* object, const char* function, const char* file, unsigned int lineNo);

    const char* typeName;
	Level level;
};

} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_STREAMREAL_H_ */
