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

#ifndef ESL_LOGGING_LEVEL_H_
#define ESL_LOGGING_LEVEL_H_

#include <esl/logging/Config.h>

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
