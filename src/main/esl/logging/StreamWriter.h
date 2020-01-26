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

#ifndef ESL_LOGGING_STREAMWRITER_H_
#define ESL_LOGGING_STREAMWRITER_H_

#include <esl/logging/Id.h>
#include <ostream>

namespace esl {
namespace logging {

class StreamWriter {
friend class StreamReal;
public:
	StreamWriter(const StreamWriter&) = delete;
	~StreamWriter();

	StreamWriter& operator=(const StreamWriter&) = delete;
	StreamWriter& operator=(StreamWriter&&) = delete;

	template<typename T2>
	inline StreamWriter& operator<<(const T2& t2) {
		oStream << t2;
		return *this;
	}

    StreamWriter& operator<<(std::ostream& (*pf)(std::ostream&));

private:
	StreamWriter(Id id, std::ostream& oStream, void* data);
	StreamWriter(StreamWriter&& streamWriter);

    bool doUnlock;
    Id id;
    std::ostream& oStream;
    void* data;
};

} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_STREAMWRITER_H_ */