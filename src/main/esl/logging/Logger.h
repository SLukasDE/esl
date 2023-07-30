/*
MIT License
Copyright (c) 2019-2023 Sven Lukas

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

#include <esl/logging/Streams.h>

#include <functional> // std::reference_wrapper<>
#include <string>
#include <vector>

namespace esl {
inline namespace v1_6 {
namespace logging {

template<Level level = defaultLevel>
class Logger {
public:
	Logger(const char* aTypeName, Logging* logging = nullptr)
	: trace(aTypeName, Level::TRACE, logging),
	  debug(aTypeName, Level::DEBUG, logging),
	  info(aTypeName, Level::INFO, logging),
	  warn(aTypeName, Level::WARN, logging),
	  error(aTypeName, Level::ERROR, logging),
	  typeName(aTypeName)
	{ }

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

extern logging::Logger<> logger;

} /* inline namespace v1_6 */
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
