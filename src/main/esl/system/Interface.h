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
#include <esl/system/Transceiver.h>
#include <esl/system/Arguments.h>
#include <esl/system/Environment.h>
#include <esl/object/Interface.h>
#include <esl/object/Values.h>

#include <boost/filesystem.hpp>

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

	enum class SignalType {
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

	using Feature = object::Interface::Object;

	class Process {
	public:
		using FileDescriptorHandle = int;

		static const FileDescriptorHandle noHandle;
		static const FileDescriptorHandle stdInHandle;
		static const FileDescriptorHandle stdOutHandle;
		static const FileDescriptorHandle stdErrHandle;

		Process() = default;
	    virtual ~Process() = default;

		virtual void setWorkingDir(std::string workingDir) = 0;
		virtual void setEnvironment(std::unique_ptr<Environment> environment) = 0;
		virtual const Environment* getEnvironment() const = 0;

		virtual void sendSignal(SignalType signal) = 0;
		virtual const void* getNativeHandle() const = 0;

		using ParameterStreams = std::map<FileDescriptorHandle, Transceiver>;
		using ParameterFeatures = std::vector<std::reference_wrapper<object::Interface::Object>>;
		virtual int execute(ParameterStreams& parameterStreams, ParameterFeatures& parameterFeatures) = 0;
	};

	using CreateProcess = std::unique_ptr<Process>(*)(Arguments arguments, const object::Values<std::string>& setting);

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
			InstallSignalHandler aInstallSignalHandler,
			RemoveSignalHandler aRemoveSignalHandler)
	: esl::module::Interface(std::move(module), getType(), std::move(implementation), getApiVersion()),
	  createProcess(aCreateProcess),
	  installSignalHandler(aInstallSignalHandler),
	  removeSignalHandler(aRemoveSignalHandler)
	{ }

	CreateProcess createProcess;

	InstallSignalHandler installSignalHandler;
	RemoveSignalHandler removeSignalHandler;
};

} /* namespace system */
} /* namespace esl */

#endif /* ESL_SYSTEM_INTERFACE_H_ */
