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

#include <esl/system/Stacktrace.h>

namespace esl {
inline namespace v1_6 {
namespace system {

void Stacktrace::init() {
	plugin::Registry::setStacktraceFactory(plugin::Registry::get().getFactory<Stacktrace>(), std::vector<std::pair<std::string, std::string>>());
}

void Stacktrace::init(plugin::Registry::StacktraceFactory create, std::vector<std::pair<std::string, std::string>> settings) {
	plugin::Registry::setStacktraceFactory(create, std::move(settings));
}

void Stacktrace::init(const std::string& implementation, std::vector<std::pair<std::string, std::string>> settings) {
	plugin::Registry::setStacktraceFactory(plugin::Registry::get().getFactory<Stacktrace>(implementation), std::move(settings));
}

} /* namespace system */
} /* inline namespace v1_6 */
} /* namespace esl */
