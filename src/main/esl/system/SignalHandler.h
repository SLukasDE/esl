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

#ifndef ESL_SYSTEM_SIGNALHANDLER_H_
#define ESL_SYSTEM_SIGNALHANDLER_H_

#include <esl/system/Interface.h>
#include <esl/object/Values.h>
#include <esl/module/Implementation.h>

#include <initializer_list>
#include <functional>

namespace esl {
namespace system {

class SignalHandler final {
public:
	using SignalType = Interface::SignalType;

	static module::Implementation& getDefault();

	SignalHandler() = delete;

	static void install(SignalType signalType, std::function<void()> handler,
			std::initializer_list<std::pair<std::string, std::string>> settings,
			const std::string& implementation = getDefault().getImplementation());
	static void install(SignalType signalType, std::function<void()> handler,
			const object::Values<std::string>& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());

	static void remove(SignalType signalType, std::function<void()> handler,
			std::initializer_list<std::pair<std::string, std::string>> settings,
			const std::string& implementation = getDefault().getImplementation());
	static void remove(SignalType signalType, std::function<void()> handler,
			const object::Values<std::string>& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());
};

} /* namespace system */
} /* namespace esl */

#endif /* ESL_SYSTEM_SIGNALHANDLER_H_ */
