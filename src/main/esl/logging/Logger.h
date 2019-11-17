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

#ifndef ESL_LOGGING_LOGGER_H_
#define ESL_LOGGING_LOGGER_H_

#include <esl/logging/Config.h>
#include <esl/logging/Level.h>
#include <esl/logging/Id.h>
#include <esl/logging/StreamEmpty.h>
#include <esl/logging/StreamReal.h>
//#include <esl/utility/StreamBuffer.h>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
#include <mutex>
#include <string>
#include <memory>
#include <functional> // std::reference_wrapper<>
#include <thread>

namespace esl {
namespace logging {

class Appender;

template<Level level = Level::INFO>
struct LoggerStreams { };

template<>
struct LoggerStreams<Level::TRACE> {
	using TraceStream = StreamReal;
	using DebugStream = StreamReal;
	using InfoStream = StreamReal;
	using WarnStream = StreamReal;
	using ErrorStream = StreamReal;
};

template<>
struct LoggerStreams<Level::DEBUG> {
	using TraceStream = StreamEmpty;
	using DebugStream = StreamReal;
	using InfoStream = StreamReal;
	using WarnStream = StreamReal;
	using ErrorStream = StreamReal;
};

template<>
struct LoggerStreams<Level::INFO> {
	using TraceStream = StreamEmpty;
	using DebugStream = StreamEmpty;
	using InfoStream = StreamReal;
	using WarnStream = StreamReal;
	using ErrorStream = StreamReal;
};

template<>
struct LoggerStreams<Level::WARN> {
	using TraceStream = StreamEmpty;
	using DebugStream = StreamEmpty;
	using InfoStream = StreamEmpty;
	using WarnStream = StreamReal;
	using ErrorStream = StreamReal;
};

template<>
struct LoggerStreams<Level::ERROR> {
	using TraceStream = StreamEmpty;
	using DebugStream = StreamEmpty;
	using InfoStream = StreamEmpty;
	using WarnStream = StreamEmpty;
	using ErrorStream = StreamReal;
};

template<>
struct LoggerStreams<Level::SILENT> {
	using TraceStream = StreamEmpty;
	using DebugStream = StreamEmpty;
	using InfoStream = StreamEmpty;
	using WarnStream = StreamEmpty;
	using ErrorStream = StreamEmpty;
};

#if ESL_LOGGING_LEVEL == ESL_LOGGING_LEVEL_SILENT
using TLoggerStreams = LoggerStreams<Level::SILENT>;
#elif ESL_LOGGING_LEVEL == ESL_LOGGING_LEVEL_ERROR
using TLoggerStreams = LoggerStreams<Level::ERROR>;
#elif ESL_LOGGING_LEVEL == ESL_LOGGING_LEVEL_WARN
using TLoggerStreams = LoggerStreams<Level::WARN>;
#elif ESL_LOGGING_LEVEL == ESL_LOGGING_LEVEL_INFO
using TLoggerStreams = LoggerStreams<Level::INFO>;
#elif ESL_LOGGING_LEVEL == ESL_LOGGING_LEVEL_DEBUG
using TLoggerStreams = LoggerStreams<Level::DEBUG>;
#elif ESL_LOGGING_LEVEL == ESL_LOGGING_LEVEL_TRACE
using TLoggerStreams = LoggerStreams<Level::TRACE>;
#else
using TLoggerStreams = LoggerStreams<>;
#endif

class Logger {
public:
	Logger(const char* typeName = "");

	// NOT thread save - call it at the beginning if needed. Default is already "true"
	// unblocked behavior makes other threads not waiting on logging, while current thread is writing to logger already.
	// If logger is used already by current thread, other threads will write to a temporary buffer.
	// - Temporary buffer is flushed to real logger, if other thread is done using the logger.
	// - If logger is still used by current thread, buffer is queued.
	// - If current thread is done using the logger, it flushes queued buffers.
	static void setUnblocked(bool isUnblocked);

	// thread safe, quaranteed by configMutex
	void setLevel(Level logLevel);
	static void setLevel(Level logLevel, const std::string& typeName);

	// thread safe, quaranteed by loggerMutex
	static void addAppender(Appender& appender);
	static std::vector<std::reference_wrapper<Appender>> getAppenders();

	TLoggerStreams::TraceStream trace;
	TLoggerStreams::DebugStream debug;
	TLoggerStreams::InfoStream info;
	TLoggerStreams::WarnStream warn;
	TLoggerStreams::ErrorStream error;

private:
	const char* typeName;
};

} /* namespace logging */

extern esl::logging::Logger logger;

} /* namespace esl */

#define ESL__LOGGER(STREAM) logger.STREAM(__func__, __FILE__, __LINE__)

#endif /* ESL_LOGGING_LOGGER_H_ */
