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

#ifndef ESL_LOGGING_LEVEL_H_
#define ESL_LOGGING_LEVEL_H_

//#include <esl/logging/Config.h>

namespace esl {
namespace logging {

enum class Level {
	TRACE,
	DEBUG,
	INFO,
	WARN,
	ERROR,
	SILENT
};

#ifndef ESL_LOGGING_LEVEL

#if defined(ESL_LOGGING_LEVEL_SILENT)
#undef ESL_LOGGING_LEVEL_SILENT
#undef ESL_LOGGING_LEVEL
#define ESL_LOGGING_LEVEL 0
#endif

#if defined(ESL_LOGGING_LEVEL_ERROR)
#undef ESL_LOGGING_LEVEL_ERROR
#undef ESL_LOGGING_LEVEL
#define ESL_LOGGING_LEVEL 1
#endif

#if defined(ESL_LOGGING_LEVEL_WARN)
#undef ESL_LOGGING_LEVEL_WARN
#undef ESL_LOGGING_LEVEL
#define ESL_LOGGING_LEVEL 2
#endif

#if defined(ESL_LOGGING_LEVEL_INFO)
#undef ESL_LOGGING_LEVEL_INFO
#undef ESL_LOGGING_LEVEL
#define ESL_LOGGING_LEVEL 3
#endif

#if defined(ESL_LOGGING_LEVEL_DEBUG)
#undef ESL_LOGGING_LEVEL_DEBUG
#undef ESL_LOGGING_LEVEL
#define ESL_LOGGING_LEVEL 4
#endif

#if defined(ESL_LOGGING_LEVEL_TRACE)
#undef ESL_LOGGING_LEVEL_TRACE
#undef ESL_LOGGING_LEVEL
#define ESL_LOGGING_LEVEL 5
#endif

#endif /* ESL_LOGGING_LEVEL */


#define ESL_LOGGING_LEVEL_SILENT 0
#define ESL_LOGGING_LEVEL_ERROR  1
#define ESL_LOGGING_LEVEL_WARN   2
#define ESL_LOGGING_LEVEL_INFO   3
#define ESL_LOGGING_LEVEL_DEBUG  4
#define ESL_LOGGING_LEVEL_TRACE  5

#ifndef ESL_LOGGING_LEVEL
#define ESL_LOGGING_LEVEL ESL_LOGGING_LEVEL_TRACE
#endif /* ESL_LOGGING_LEVEL */


#ifndef ESL_LOGGING_LEVEL_BUILD

#if defined(ESL_LOGGING_LEVEL_BUILD_SILENT)
#undef ESL_LOGGING_LEVEL_BUILD_SILENT
#undef ESL_LOGGING_LEVEL_BUILD
#define ESL_LOGGING_LEVEL_BUILD ESL_LOGGING_LEVEL_SILENT
#endif

#if defined(ESL_LOGGING_LEVEL_BUILD_ERROR)
#undef ESL_LOGGING_LEVEL_BUILD_ERROR
#undef ESL_LOGGING_LEVEL_BUILD
#define ESL_LOGGING_LEVEL_BUILD ESL_LOGGING_LEVEL_ERROR
#endif

#if defined(ESL_LOGGING_LEVEL_BUILD_WARN)
#undef ESL_LOGGING_LEVEL_BUILD_WARN
#undef ESL_LOGGING_LEVEL_BUILD
#define ESL_LOGGING_LEVEL_BUILD ESL_LOGGING_LEVEL_WARN
#endif

#if defined(ESL_LOGGING_LEVEL_BUILD_INFO)
#undef ESL_LOGGING_LEVEL_BUILD_INFO
#undef ESL_LOGGING_LEVEL_BUILD
#define ESL_LOGGING_LEVEL_BUILD ESL_LOGGING_LEVEL_INFO
#endif

#if defined(ESL_LOGGING_LEVEL_BUILD_DEBUG)
#undef ESL_LOGGING_LEVEL_BUILD_DEBUG
#undef ESL_LOGGING_LEVEL_BUILD
#define ESL_LOGGING_LEVEL_BUILD ESL_LOGGING_LEVEL_DEBUG
#endif

#if defined(ESL_LOGGING_LEVEL_BUILD_TRACE)
#undef ESL_LOGGING_LEVEL_BUILD_TRACE
#undef ESL_LOGGING_LEVEL_BUILD
#define ESL_LOGGING_LEVEL_BUILD ESL_LOGGING_LEVEL_TRACE
#endif

#endif /* ESL_LOGGING_LEVEL_BUILD */



#ifndef ESL_LOGGING_LEVEL_BUILD
#define ESL_LOGGING_LEVEL_BUILD ESL_LOGGING_LEVEL_TRACE
#endif /* ESL_LOGGING_LEVEL_BUILD */

#if ESL_LOGGING_LEVEL_BUILD == ESL_LOGGING_LEVEL_SILENT
constexpr Level defaultLevel = Level::SILENT;
#elif ESL_LOGGING_LEVEL_BUILD == ESL_LOGGING_LEVEL_ERROR
constexpr Level defaultLevel = Level::ERROR;
#elif ESL_LOGGING_LEVEL_BUILD == ESL_LOGGING_LEVEL_WARN
constexpr Level defaultLevel = Level::WARN;
#elif ESL_LOGGING_LEVEL_BUILD == ESL_LOGGING_LEVEL_INFO
constexpr Level defaultLevel = Level::INFO;
#elif ESL_LOGGING_LEVEL_BUILD == ESL_LOGGING_LEVEL_DEBUG
constexpr Level defaultLevel = Level::DEBUG;
#else // ESL_LOGGING_LEVEL_BUILD == ESL_LOGGING_LEVEL_TRACE
constexpr Level defaultLevel = Level::TRACE;
#endif

} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_LEVEL_H_ */
