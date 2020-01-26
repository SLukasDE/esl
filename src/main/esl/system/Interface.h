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

#ifndef ESL_SYSTEM_INTERFACE_H_
#define ESL_SYSTEM_INTERFACE_H_

#include <esl/module/Interface.h>
#include <esl/Module.h>
#include <memory>
#include <list>
#include <functional>

namespace esl {
namespace system {

struct Interface : esl::module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class Process {
	public:
	    class Output {
	    public:
	    	Output() = default;
	    	virtual ~Output() = default;

	    	virtual std::size_t read(void* buffer, std::size_t s) = 0;
	    	virtual bool setBlocking(bool blocking) = 0;
	    };

	    Process() = default;
	    virtual ~Process() = default;

	    virtual void enableTimeMeasurement(bool enabled) = 0;
	    virtual void setWorkingDirectory(const std::string& workingDirectory) = 0;

	    //virtual void setOutput(std::unique_ptr<Output> output, bool stdOut, bool stdErr) = 0;
	    virtual void setStdOut(Output* output) = 0;
	    //virtual Output* getStdOut() const = 0;

	    virtual void setStdErr(Output* output) = 0;
	    //virtual Output* getStdErr() const = 0;

	    /* return true on success */
	    virtual bool execute(const std::string& executable, const std::list<std::string>& arguments) = 0;

	    virtual int wait() = 0;
	    virtual bool isRunning() = 0;
	    virtual bool isFailed() = 0;

	    virtual unsigned int getTimeRealMS() const = 0;
	    virtual unsigned int getTimeUserMS() const = 0;
	    virtual unsigned int getTimeSysMS() const = 0;
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

	using CreateProcess = Process* (*)();
	using CreateProcessOutputDefault = Process::Output* (*)();
	using CreateProcessOutputPipe = Process::Output* (*)();
	using CreateProcessOutputFile = Process::Output* (*)(const std::string& filename);

	using InstallSignalHandler = void (*)(SignalType signalType, std::function<void()> handler);
	using RemoveSignalHandler = void (*)(SignalType signalType, std::function<void()> handler);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getId() {
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
			CreateProcessOutputDefault aCreateProcessOutputDefault,
			CreateProcessOutputPipe aCreateProcessOutputPipe,
			CreateProcessOutputFile aCreateProcessOutputFile,
			InstallSignalHandler aInstallSignalHandler,
			RemoveSignalHandler aRemoveSignalHandler)
	: esl::module::Interface(std::move(module), getId(), std::move(implementation), getApiVersion()),
	  createProcess(aCreateProcess),
	  createProcessOutputDefault(aCreateProcessOutputDefault),
	  createProcessOutputPipe(aCreateProcessOutputPipe),
	  createProcessOutputFile(aCreateProcessOutputFile),
	  installSignalHandler(aInstallSignalHandler),
	  removeSignalHandler(aRemoveSignalHandler)
	{ }

	CreateProcess createProcess;
	CreateProcessOutputDefault createProcessOutputDefault;
	CreateProcessOutputPipe createProcessOutputPipe;
	CreateProcessOutputFile createProcessOutputFile;

	InstallSignalHandler installSignalHandler;
	RemoveSignalHandler removeSignalHandler;
};

} /* namespace system */
} /* namespace esl */

#endif /* ESL_SYSTEM_INTERFACE_H_ */
