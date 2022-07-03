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

#ifndef ESL_LOGGING_LOGGING_H_
#define ESL_LOGGING_LOGGING_H_

#include <esl/logging/Appender.h>
#include <esl/logging/Level.h>
#include <esl/logging/Location.h>
#include <esl/logging/OStream.h>

#include <memory>
#include <string>
#include <thread>

namespace esl {
namespace logging {

class Logging {
public:
	virtual ~Logging() = default;

	virtual void setUnblocked(bool isUnblocked) = 0;
	virtual void setLevel(Level logLevel, const std::string& typeName) = 0;
	virtual void* addAppender(Appender& appender) = 0;
	virtual void removeAppender(void* handle) = 0;
	virtual bool isEnabled(const char* typeName, Level level) = 0;
	virtual std::unique_ptr<OStream> createOStream(const Location& location) = 0;
	virtual unsigned int getThreadNo(std::thread::id threadId) = 0;
};

} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_LOGGING_H_ */
