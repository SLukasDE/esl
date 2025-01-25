/*
MIT License
Copyright (c) 2019-2025 Sven Lukas

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

#ifndef ESL_MONITORING_LOGGER_H_
#define ESL_MONITORING_LOGGER_H_

#include <esl/monitoring/Streams.h>

namespace esl {
inline namespace v1_6 {
namespace monitoring {

template<Streams::Level level>
struct Logger;

template<>
struct Logger<Streams::Level::trace> : Streams {
	Logger(const char* aTypeName)
	: Streams(aTypeName),
	  trace(aTypeName, Level::trace),
	  debug(aTypeName, Level::debug),
	  info(aTypeName, Level::info),
	  warn(aTypeName, Level::warn),
	  error(aTypeName, Level::error)
	{ }

	Real trace;
	Real debug;
	Real info;
	Real warn;
	Real error;
};

template<>
struct Logger<Streams::Level::debug> : Streams {
	Logger(const char* aTypeName)
	: Streams(aTypeName),
	  debug(aTypeName, Level::debug),
	  info(aTypeName, Level::info),
	  warn(aTypeName, Level::warn),
	  error(aTypeName, Level::error)
	{ }

	Empty trace;
	Real debug;
	Real info;
	Real warn;
	Real error;
};

template<>
struct Logger<Streams::Level::info> : Streams {
	Logger(const char* aTypeName)
	: Streams(aTypeName),
	  info(aTypeName, Level::info),
	  warn(aTypeName, Level::warn),
	  error(aTypeName, Level::error)
	{ }

	Empty trace;
	Empty debug;
	Real info;
	Real warn;
	Real error;
};

template<>
struct Logger<Streams::Level::warn> : Streams {
	Logger(const char* aTypeName)
	: Streams(aTypeName),
	  warn(aTypeName, Level::warn),
	  error(aTypeName, Level::error)
	{ }

	Empty trace;
	Empty debug;
	Empty info;
	Real warn;
	Real error;
};

template<>
struct Logger<Streams::Level::error> : Streams {
	Logger(const char* aTypeName)
	: Streams(aTypeName),
	  error(aTypeName, Level::error)
	{ }

	Empty trace;
	Empty debug;
	Empty info;
	Empty warn;
	Real error;
};

template<>
struct Logger<Streams::Level::silent> : Streams {
	Logger(const char* aTypeName)
	: Streams(aTypeName)
	{ }

	Empty trace;
	Empty debug;
	Empty info;
	Empty warn;
	Empty error;
};

} /* namespace monitoring */
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

#endif /* ESL_MONITORING_LOGGER_H_ */
