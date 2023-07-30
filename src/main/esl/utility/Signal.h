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

#ifndef ESL_UTILITY_SIGNAL_H_
#define ESL_UTILITY_SIGNAL_H_

#include <esl/utility/Enum.h>

#include <string>

namespace esl {
inline namespace v1_6 {
namespace utility {

enum SignalType {
    unknown,
	hangUp, // ?, controlling terminal closed
    interrupt, // interrupt process stream, ctrl-C
    quit,      // like ctrl-C but with a core dump, interruption by error in code, ctl-/
	ill,
	trap,
	abort,
	busError,
	floatingPointException,
	segmentationViolation,
	user1,
	user2,
	alarm,
	child,
	stackFault,
    terminate, // terminate whenever/soft kill, typically sends SIGHUP as well?
    pipe,
	kill       // terminate immediately/hard kill, use when 15 doesn't work or when something disasterous might happen if process is allowed to cont., kill -9
};

using Signal = Enum<SignalType, SignalType::unknown>;

template<>
const std::string& Signal::toString(SignalType signalType) noexcept;

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_SIGNAL_H_ */
