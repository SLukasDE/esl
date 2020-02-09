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

#ifndef ESL_LOGGING_APPENDER_OSTREAM_H_
#define ESL_LOGGING_APPENDER_OSTREAM_H_

#include <esl/logging/Appender.h>
#include <esl/logging/Level.h>
#include <esl/logging/Location.h>
#include <string>
#include <ostream>

namespace esl {
namespace logging {
namespace appender {

class OStream : public Appender {
public:
	OStream(std::ostream& oStreamTrace,
	std::ostream& oStreamDebug,
	std::ostream& oStreamInfo,
	std::ostream& oStreamWarn,
	std::ostream& oStreamError);

protected:
	void flush() override;
	void write(const Location& location, const char* ptr, std::size_t size) override;

private:
	bool isFirstCharacterInLine = true;
	Location lastLocation;
	std::ostream& oStreamTrace;
	std::ostream& oStreamDebug;
	std::ostream& oStreamInfo;
	std::ostream& oStreamWarn;
	std::ostream& oStreamError;

	std::ostream& getOStream(Level level);
};

} /* namespace appender */
} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_APPENDER_OSTREAM_H_ */
