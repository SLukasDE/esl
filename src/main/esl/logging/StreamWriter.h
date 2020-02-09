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

#ifndef ESL_LOGGING_STREAMWRITER_H_
#define ESL_LOGGING_STREAMWRITER_H_

//#include <ostream>
#include <esl/logging/OStream.h>
#include <memory>

namespace esl {
namespace logging {

class StreamWriter {
friend class StreamReal;
public:
	StreamWriter(const StreamWriter&) = delete;

	StreamWriter& operator=(const StreamWriter&) = delete;
	StreamWriter& operator=(StreamWriter&&) = delete;

	template<typename T>
	inline StreamWriter& operator<<(const T& t) {
		if(oStream && oStream->getOStream()) {
			*oStream->getOStream() << t;
		}
		return *this;
	}

    StreamWriter& operator<<(std::ostream& (*pf)(std::ostream&));

    template<typename T>
	inline StreamWriter& write(const T& t) {
		if(oStream && oStream->getOStream()) {
			*oStream->getOStream() << t;
		}
		return *this;
	}

    template<typename T, typename... Args>
	inline StreamWriter& write(const T& t, Args... args) {
		if(oStream && oStream->getOStream()) {
			*oStream->getOStream() << t;
			return write(args...);
		}
		return *this;
	}


private:
	StreamWriter(std::unique_ptr<OStream> oStream);
	StreamWriter(StreamWriter&& streamWriter);

    std::unique_ptr<OStream> oStream;
};

} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_STREAMWRITER_H_ */
