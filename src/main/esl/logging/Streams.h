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

#ifndef ESL_LOGGING_STREAMS_H_
#define ESL_LOGGING_STREAMS_H_

#include <esl/logging/Level.h>
#include <esl/logging/StreamEmpty.h>
#include <esl/logging/StreamReal.h>

namespace esl {
namespace logging {

template<Level level>
struct Streams;

template<>
struct Streams<Level::TRACE> {
	using Trace = StreamReal;
	using Debug = StreamReal;
	using Info = StreamReal;
	using Warn = StreamReal;
	using Error = StreamReal;
};

template<>
struct Streams<Level::DEBUG> {
	using Trace = StreamEmpty;
	using Debug = StreamReal;
	using Info = StreamReal;
	using Warn = StreamReal;
	using Error = StreamReal;
};

template<>
struct Streams<Level::INFO> {
	using Trace = StreamEmpty;
	using Debug = StreamEmpty;
	using Info = StreamReal;
	using Warn = StreamReal;
	using Error = StreamReal;
};

template<>
struct Streams<Level::WARN> {
	using Trace = StreamEmpty;
	using Debug = StreamEmpty;
	using Info = StreamEmpty;
	using Warn = StreamReal;
	using Error = StreamReal;
};

template<>
struct Streams<Level::ERROR> {
	using Trace = StreamEmpty;
	using Debug = StreamEmpty;
	using Info = StreamEmpty;
	using Warn = StreamEmpty;
	using Error = StreamReal;
};

template<>
struct Streams<Level::SILENT> {
	using Trace = StreamEmpty;
	using Debug = StreamEmpty;
	using Info = StreamEmpty;
	using Warn = StreamEmpty;
	using Error = StreamEmpty;
};

} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_STREAMS_H_ */
