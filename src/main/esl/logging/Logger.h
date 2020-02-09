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

#ifndef ESL_LOGGING_LOGGER_H_
#define ESL_LOGGING_LOGGER_H_

#include <esl/logging/Config.h>
#include <esl/logging/Level.h>
#include <esl/logging/Streams.h>

#include <vector>
#include <string>
#include <functional> // std::reference_wrapper<>

namespace esl {
namespace logging {

class Appender;

// NOT thread save - call it at the beginning if needed. Default is already "true"
// unblocked behavior makes other threads not waiting on logging, while current thread is writing to logger already.
// If logger is used already by current thread, other threads will write to a temporary buffer.
// - Temporary buffer is flushed to real logger, if other thread is done using the logger.
// - If logger is still used by current thread, buffer is queued.
// - If current thread is done using the logger, it flushes queued buffers.
void setUnblocked(bool isUnblocked);

// thread safe, quaranteed by configMutex
void setLevel(Level logLevel, const std::string& typeName);

// thread safe, quaranteed by loggerMutex
void addAppender(Appender& appender);

template<Level level = defaultLevel>
class Logger {
public:
	Logger(const char* aTypeName = "")
	: trace(aTypeName, Level::TRACE),
	  debug(aTypeName, Level::DEBUG),
	  info(aTypeName, Level::INFO),
	  warn(aTypeName, Level::WARN),
	  error(aTypeName, Level::ERROR),
	  typeName(aTypeName)
	{ }

	// NOT thread save - call it at the beginning if needed. Default is already "true"
	// unblocked behavior makes other threads not waiting on logging, while current thread is writing to logger already.
	// If logger is used already by current thread, other threads will write to a temporary buffer.
	// - Temporary buffer is flushed to real logger, if other thread is done using the logger.
	// - If logger is still used by current thread, buffer is queued.
	// - If current thread is done using the logger, it flushes queued buffers.
//	static void setUnblocked(bool isUnblocked);

	// thread safe, quaranteed by configMutex
//	static void setLevel(Level logLevel, const std::string& typeName);
	void setLevel(Level logLevel);

	// thread safe, quaranteed by loggerMutex
//	static void addAppender(Appender& appender);
//	static std::vector<std::reference_wrapper<Appender>> getAppenders();

    template<typename... Args>
	static inline void write(StreamReal& streamReal, const void* object, const char* function, const char* file, unsigned int lineNo, Args... args) {
    	streamReal(object, function, file, lineNo).write(args...);
    }

    template<typename... Args>
	static inline void write(StreamEmpty& streamEmpty, const void* object, const char* function, const char* file, unsigned int lineNo, Args... args) { }


	typename Streams<level>::Trace trace;
	typename Streams<level>::Debug debug;
	typename Streams<level>::Info info;
	typename Streams<level>::Warn warn;
	typename Streams<level>::Error error;

private:
	const char* typeName;
};

} /* namespace logging */

extern esl::logging::Logger<> logger;

} /* namespace esl */

#define ESL__LOGGER_ERROR_OBJ(OBJ, ...) logger.write(logger.error, OBJ, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_ERROR_THIS(...)     logger.write(logger.error, this, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_ERROR(...)          logger.write(logger.error, nullptr, __func__, __FILE__, __LINE__, __VA_ARGS__);

#define ESL__LOGGER_WARN_OBJ(OBJ, ...) logger.write(logger.warn, OBJ, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_WARN_THIS(...)     logger.write(logger.warn, this, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_WARN(...)          logger.write(logger.warn, nullptr, __func__, __FILE__, __LINE__, __VA_ARGS__);

#define ESL__LOGGER_INFO_OBJ(OBJ, ...) logger.write(logger.info, OBJ, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_INFO_THIS(...)     logger.write(logger.info, this, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_INFO(...)          logger.write(logger.info, nullptr, __func__, __FILE__, __LINE__, __VA_ARGS__);

#define ESL__LOGGER_DEBUG_OBJ(OBJ, ...) logger.write(logger.debug, OBJ, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_DEBUG_THIS(...)     logger.write(logger.debug, this, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_DEBUG(...)          logger.write(logger.debug, nullptr, __func__, __FILE__, __LINE__, __VA_ARGS__);

#define ESL__LOGGER_TRACE_OBJ(OBJ, ...) logger.write(logger.trace, OBJ, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_TRACE_THIS(...)     logger.write(logger.trace, this, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_TRACE(...)          logger.write(logger.trace, nullptr, __func__, __FILE__, __LINE__, __VA_ARGS__);

#endif /* ESL_LOGGING_LOGGER_H_ */
