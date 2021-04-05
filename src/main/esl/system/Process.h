/*
MIT License
Copyright (c) 2019-2021 Sven Lukas

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

#ifndef ESL_SYSTEM_PROCESS_H_
#define ESL_SYSTEM_PROCESS_H_

#include <esl/system/Interface.h>
#include <esl/system/Transceiver.h>
#include <esl/system/Arguments.h>
#include <esl/system/Environment.h>
#include <esl/object/Values.h>
#include <esl/module/Implementation.h>

#include <initializer_list>
#include <string>
#include <memory>
#include <map>

namespace esl {
namespace system {

class Process final {
public:
	static module::Implementation& getDefault();

	Process(Arguments arguments,
			std::initializer_list<std::pair<std::string, std::string>> settings,
			const std::string& implementation = getDefault().getImplementation());
	Process(Arguments arguments,
			const object::Values<std::string>& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());

	std::map<Interface::Process::FileDescriptorHandle, Transceiver> transceivers;

	void setWorkingDir(std::string workingDir);
	void setEnvironment(std::unique_ptr<Environment> environment);
	const Environment* getEnvironment() const;

	void sendSignal(Interface::SignalType signal);
	const void* getNativeHandle() const;

	int execute();
	int execute(Interface::Feature& feature);

	template<typename... Args>
	int execute(Interface::Feature& feature, Args&... args) {
		Interface::Process::ParameterFeatures parameterFeatures;

		parameterFeatures.emplace_back(std::ref(feature));
    	return execute(parameterFeatures, args...);
	}

private:
	int execute(Interface::Process::ParameterFeatures& parameterFeatures);

	template<typename... Args>
	int execute(Interface::Process::ParameterFeatures& parameterFeatures, Interface::Feature& feature, Args&... args) {
		parameterFeatures.emplace_back(std::ref(feature));
    	return execute(parameterFeatures, args...);
	}

	std::unique_ptr<Interface::Process> process;
	std::vector<std::reference_wrapper<object::Interface::Object>> parameterFeatures;
};

} /* namespace system */
} /* namespace esl */

#endif /* ESL_SYSTEM_PROCESS_H_ */
