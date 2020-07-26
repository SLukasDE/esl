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

#include <esl/system/process/Arguments.h>
#include <esl/system/process/Environment.h>
#include <esl/object/Values.h>

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

	class FileDescriptor {
	public:
		using Handle = int;

		static const Handle noHandle = -1;
		static const Handle stdInHandle = 0;
		static const Handle stdOutHandle = 1;
		static const Handle stdErrHandle = 2;

		static const std::size_t npos = static_cast<std::size_t>(-1);

		FileDescriptor() = default;
		virtual ~FileDescriptor() = default;

		virtual std::size_t read(void* data, std::size_t size) = 0;
		virtual std::size_t write(const void* data, std::size_t size) = 0;
	};

	class Consumer {
	public:
		Consumer() = default;
		virtual ~Consumer() = default;

		virtual std::size_t read(FileDescriptor& fileDescriptor) = 0;
	};
/*
	class ConsumerFile : public Consumer {
	public:
	};
*/
	class Producer {
	public:
		Producer() = default;
		virtual ~Producer() = default;

		/* return: FileDescriptor::npos
		 *           if there is no more data to produce (IMPORTANT)
		 *
		 *         Number of characters written to fileDescriptor
		 *           if there are data available to write to fileDescripor
		 *           (produced now or queued from previous call). */
		virtual std::size_t write(FileDescriptor& fileDescriptor) = 0;
	};

	class ProducerFile : public Producer {
	public:
		virtual std::size_t getFileSize() const = 0;
	};

	class Feature {
	public:
		virtual ~Feature() = default;
	};

	class Process {
	public:
		struct ParameterStream {
			Producer* producer = nullptr;
			Consumer* consumer = nullptr;
		};
		using ParameterStreams = std::map<FileDescriptor::Handle, ParameterStream>;

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

	using CreateProcess = std::unique_ptr<Process>(*)(process::Arguments arguments, std::string workingDir);
	using CreateProcessWithEnvironment = std::unique_ptr<Process>(*)(process::Arguments arguments, process::Environment environment, std::string workingDir);
	using CreateConsumerFile = std::unique_ptr<Consumer>(*)(std::string filename, const object::Values<std::string>& values);
	using CreateProducerFile = std::unique_ptr<ProducerFile>(*)(std::string filename, const object::Values<std::string>& values);

	using InstallSignalHandler = void (*)(SignalType signalType, std::function<void()> handler);
	using RemoveSignalHandler = void (*)(SignalType signalType, std::function<void()> handler);

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
			CreateConsumerFile aCreateConsumerFile,
			CreateProducerFile aCreateProducerFile,
			InstallSignalHandler aInstallSignalHandler,
			RemoveSignalHandler aRemoveSignalHandler)
	: esl::module::Interface(std::move(module), getType(), std::move(implementation), getApiVersion()),
	  createProcess(aCreateProcess),
	  createProcessWithEnvironment(aCreateProcessWithEnvironment),
	  createConsumerFile(aCreateConsumerFile),
	  createProducerFile(aCreateProducerFile),
	  installSignalHandler(aInstallSignalHandler),
	  removeSignalHandler(aRemoveSignalHandler)
	{ }

	CreateProcess createProcess;
	CreateProcessWithEnvironment createProcessWithEnvironment;
	CreateConsumerFile createConsumerFile;
	CreateProducerFile createProducerFile;

	InstallSignalHandler installSignalHandler;
	RemoveSignalHandler removeSignalHandler;
};

} /* namespace system */
} /* namespace esl */

#endif /* ESL_SYSTEM_INTERFACE_H_ */
