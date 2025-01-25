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

#include <esl/system/exception/ProcessError.h>

namespace esl {
inline namespace v1_6 {
namespace system {
namespace exception {

namespace {
static constexpr const char* defaultMessage = "process error";
}

ProcessError::ProcessError(int aErrorCode)
: std::runtime_error(defaultMessage),
  errorCode(aErrorCode)
{ }

ProcessError::ProcessError(int aErrorCode, const char* message)
: std::runtime_error(message),
  errorCode(aErrorCode)
{ }

ProcessError::ProcessError(int aErrorCode, const std::string& message)
: std::runtime_error(message),
  errorCode(aErrorCode)
{ }

int ProcessError::getErrorCode() const noexcept {
	return errorCode;
}

} /* namespace exception */
} /* namespace system */
} /* inline namespace v1_6 */
} /* namespace esl */
