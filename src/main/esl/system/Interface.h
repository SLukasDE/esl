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

#ifndef ESL_SYSTEM_INTERFACE_H_
#define ESL_SYSTEM_INTERFACE_H_

#include <esl/module/Interface.h>
#include <esl/Module.h>

#include <esl/system/process/Arguments.h>
#include <esl/system/process/Environment.h>
#include <esl/object/Values.h>
#include <esl/utility/Consumer.h>
#include <esl/utility/Producer.h>

#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace esl {
namespace system {

struct Interface : esl::module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class Feature {
	public:
		virtual ~Feature() = default;
	};

	class Process {
	public:
		using FileDescriptorHandle = int;

		static const FileDescriptorHandle noHandle;
		static const FileDescriptorHandle stdInHandle;
		static const FileDescriptorHandle stdOutHandle;
		static const FileDescriptorHandle stdErrHandle;

		struct ParameterStream {
			utility::Producer* producer = nullptr;
			utility::Consumer* consumer = nullptr;
		};
		using ParameterStreams = std::map<FileDescriptorHandle, ParameterStream>;

		using ParameterFeatures = std::vector<std::reference_wrapper<Feature>>;

		Process() = default;
	    virtual ~Process() = default;

		virtual int execute(const ParameterStreams& parameterStreams, ParameterFeatures& parameterFeatures) = 0;
	};

	enum class SignalType {
	    unknown,
		hangUp,
	    interrupt,
	    quit,
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
	    terminate,
	    pipe
	};

	using CreateProcess = std::unique_ptr<Process>(*)(process::Arguments arguments, std::string workingDir, const object::Values<std::string>& setting);
	using CreateProcessWithEnvironment = std::unique_ptr<Process>(*)(process::Arguments arguments, process::Environment environment, std::string workingDir, const object::Values<std::string>& setting);

	using InstallSignalHandler = void (*)(SignalType signalType, std::function<void()> handler, const object::Values<std::string>& setting);
	using RemoveSignalHandler = void (*)(SignalType signalType, std::function<void()> handler, const object::Values<std::string>& setting);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-system";
	}

	static inline const std::string& getApiVersion() {
		return esl::getModule().getApiVersion();
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	Interface(std::string module, std::string implementation,
			CreateProcess aCreateProcess,
			CreateProcessWithEnvironment aCreateProcessWithEnvironment,
			InstallSignalHandler aInstallSignalHandler,
			RemoveSignalHandler aRemoveSignalHandler)
	: esl::module::Interface(std::move(module), getType(), std::move(implementation), getApiVersion()),
	  createProcess(aCreateProcess),
	  createProcessWithEnvironment(aCreateProcessWithEnvironment),
	  installSignalHandler(aInstallSignalHandler),
	  removeSignalHandler(aRemoveSignalHandler)
	{ }

	CreateProcess createProcess;
	CreateProcessWithEnvironment createProcessWithEnvironment;

	InstallSignalHandler installSignalHandler;
	RemoveSignalHandler removeSignalHandler;
};

} /* namespace system */
} /* namespace esl */

#endif /* ESL_SYSTEM_INTERFACE_H_ */
