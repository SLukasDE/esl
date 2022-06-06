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

#include <esl/system/signal/Signal.h>

namespace esl {
namespace system {
namespace signal {

module::Implementation& Signal::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

Signal::Signal(const std::vector<std::pair<std::string, std::string>>& settings, const std::string& implementation)
: signal(getModule().getInterface<Interface>(implementation).createSignal(settings))
{ }

Signal::Handler Signal::createHandler(const utility::Signal& signalType, std::function<void()> function) {
	return signal->createHandler(signalType, function);
}

} /* namespace signal */
} /* namespace system */
} /* namespace esl */
