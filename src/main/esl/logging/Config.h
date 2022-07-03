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

#ifndef ESL_LOGGING_CONFIG_H_
#define ESL_LOGGING_CONFIG_H_

#include <esl/logging/Appender.h>
#include <esl/logging/Level.h>
#include <esl/logging/Location.h>
#include <esl/logging/OStream.h>

#include <thread>
#include <memory>
#include <string>

namespace esl {
namespace logging {

class Config final {
public:
	Config() = delete;

	//class Appender;

	// NOT thread save - call it at the beginning if needed. Default is already "true"
	// unblocked behavior makes other threads not waiting on logging, while current thread is writing to logger already.
	// If logger is used already by current thread, other threads will write to a temporary buffer.
	// - Temporary buffer is flushed to real logger, if other thread is done using the logger.
	// - If logger is still used by current thread, buffer is queued.
	// - If current thread is done using the logger, it flushes queued buffers.
	static void setUnblocked(bool isUnblocked);

	// thread safe, quaranteed by configMutex
	static void setLevel(Level logLevel, const std::string& typeName);

	// thread safe, quaranteed by loggerMutex
	static void addAppender(Appender& appender);

	static bool isEnabled(const char* typeName, Level level);

	static std::unique_ptr<OStream> createOStream(const Location& location);

	static unsigned int getThreadNo(std::thread::id threadId);
};

} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_CONFIG_H_ */
