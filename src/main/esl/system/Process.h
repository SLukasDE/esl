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
#include <esl/system/process/Arguments.h>
#include <esl/system/process/Environment.h>
#include <esl/object/Values.h>
#include <esl/utility/Consumer.h>
#include <esl/utility/Producer.h>
#include <esl/module/Implementation.h>

#include <initializer_list>
#include <string>
#include <memory>

namespace esl {
namespace system {

class Process final : public Interface::Process {
public:
	static module::Implementation& getDefault();

	Process(process::Arguments arguments,
			std::initializer_list<std::pair<std::string, std::string>> settings,
			const std::string& implementation = getDefault().getImplementation());
	Process(process::Arguments arguments, std::string workingDir,
			std::initializer_list<std::pair<std::string, std::string>> settings,
			const std::string& implementation = getDefault().getImplementation());
	Process(process::Arguments arguments, std::string workingDir = "",
			const object::Values<std::string>& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());
	Process(process::Arguments arguments, process::Environment environment,
			std::initializer_list<std::pair<std::string, std::string>> settings,
			const std::string& implementation = getDefault().getImplementation());
	Process(process::Arguments arguments, process::Environment environment, std::string workingDir,
			std::initializer_list<std::pair<std::string, std::string>> settings,
			const std::string& implementation = getDefault().getImplementation());
	Process(process::Arguments arguments, process::Environment environment, std::string workingDir = "",
			const object::Values<std::string>& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());

	int execute();
	int execute(Interface::Process::FileDescriptorHandle handle);
	int execute(utility::Producer& producer, Interface::Process::FileDescriptorHandle handle);
	int execute(utility::Consumer& consumer, Interface::Process::FileDescriptorHandle handle);
	int execute(Interface::Feature& feature);
	int execute(const ParameterStreams& parameterStreams, ParameterFeatures& parameterFeatures) override;

	template<typename... Args>
	int execute(Interface::Process::FileDescriptorHandle handle, Args&... args) {
    	ParameterStreams parameterStreams;
    	ParameterFeatures parameterFeatures;

    	addParameterStream(parameterStreams, handle, nullptr, nullptr);
    	return execute(parameterStreams, parameterFeatures, args...);
	}

	template<typename... Args>
	int execute(utility::Producer& producer, Interface::Process::FileDescriptorHandle handle, Args&... args) {
    	ParameterStreams parameterStreams;
    	ParameterFeatures parameterFeatures;

    	addParameterStream(parameterStreams, handle, &producer, nullptr);
    	return execute(parameterStreams, parameterFeatures, args...);
	}

	template<typename... Args>
	int execute(utility::Consumer& consumer, Interface::Process::FileDescriptorHandle handle, Args&... args) {
		ParameterStreams parameterStreams;
		ParameterFeatures parameterFeatures;

		addParameterStream(parameterStreams, handle, nullptr, &consumer);
    	return execute(parameterStreams, parameterFeatures, args...);
	}

	template<typename... Args>
	int execute(Interface::Feature& feature, Args&... args) {
		ParameterFeatures parameterFeatures;

		parameterFeatures.emplace_back(std::ref(feature));
    	return execute(ParameterStreams(), parameterFeatures, args...);
	}

private:
	template<typename... Args>
	int execute(ParameterStreams& parameterStreams, ParameterFeatures& parameterFeatures, Interface::Process::FileDescriptorHandle handle, Args&... args) {
		addParameterStream(parameterStreams, handle, nullptr, nullptr);
		return execute(parameterStreams, parameterFeatures, args...);
	}

	template<typename... Args>
	int execute(ParameterStreams& parameterStreams, ParameterFeatures& parameterFeatures, utility::Producer& producer, Interface::Process::FileDescriptorHandle handle, Args&... args) {
		addParameterStream(parameterStreams, handle, &producer, nullptr);
		return execute(parameterStreams, parameterFeatures, args...);
	}

	template<typename... Args>
	int execute(ParameterStreams& parameterStreams, ParameterFeatures& parameterFeatures, utility::Consumer& consumer, Interface::Process::FileDescriptorHandle handle, Args&... args) {
		addParameterStream(parameterStreams, handle, nullptr, &consumer);
		return execute(parameterStreams, parameterFeatures, args...);
	}

	template<typename... Args>
	int execute(ParameterStreams& parameterStreams, ParameterFeatures& parameterFeatures, Interface::Feature& feature, Args&... args) {
		parameterFeatures.emplace_back(std::ref(feature));
    	return execute(ParameterStreams(), parameterFeatures, args...);
	}

	static void addParameterStream(ParameterStreams& parameterStreams, Interface::Process::FileDescriptorHandle handle, utility::Producer* producer, utility::Consumer* consumer);

	std::unique_ptr<Interface::Process> process;
};

} /* namespace system */
} /* namespace esl */

#endif /* ESL_SYSTEM_PROCESS_H_ */
