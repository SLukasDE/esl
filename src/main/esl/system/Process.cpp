/*
MIT License
Copyright (c) 2019 Sven Lukas

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

#include <esl/system/Process.h>
#include <esl/logging/Logger.h>
#include <esl/Stacktrace.h>

namespace esl {
namespace system {

namespace {

Interface::Process& createProcess() {
	esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion());
	const Interface* interface = static_cast<const Interface*>(esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion()));

	if(interface == nullptr) {
		throw esl::addStacktrace(std::runtime_error("no implementation available for \"esl::system::Process\""));
	}

	return *interface->createProcess();
}

}

Process::Process()
: // Interface::Process(),
  process(createProcess())
{ }

Process::~Process() {
    wait();
}

void Process::enableTimeMeasurement(bool enabled) {
	process.enableTimeMeasurement(enabled);
}

void Process::setWorkingDirectory(const std::string& workingDirectory) {
	process.setWorkingDirectory(workingDirectory);
}

void Process::setOutput(std::unique_ptr<Process::Output> output, bool stdOut, bool stdErr) {
	/* make "output" and "output->baseOutput" to
	 * raw pointers "outputPtr" and "outputBasePtr"
	 * and let's control "output" by our self */

	Process::Output* outputPtr = nullptr;
	Interface::Process::Output* outputBasePtr = nullptr;

	if(output) {
		outputBasePtr = output->basePtr.get();
		outputPtr = output.get();
		output.release();
	}

	if(stdOut) {
		process.setStdOut(outputBasePtr);
	}
	if(stdErr) {
		process.setStdErr(outputBasePtr);
	}


	if(stdOut) {
		/* if previous output was specified for stdErr and stdErr,
		 * then we have do move "outErr" to "err"
		 */
		if(outPtr == errPtr) {
			err = std::move(outErr);
		}
		outErr.reset(outputPtr);

		outPtr = outputPtr;

		if(stdErr) {
			errPtr = outputPtr;
		}
	}
	else if(stdErr) {
		err.reset(outputPtr);
		errPtr = outputPtr;
	}

}

Process::Output* Process::getStdOut() const {
	return outPtr;
//	return process.getStdOut();
}

Process::Output* Process::getStdErr() const {
	return errPtr;
//	return process.getStdErr();
}

bool Process::execute(const std::string& executable, const std::list<std::string>& arguments) {
	return process.execute(executable, arguments);
}

int Process::wait() {
	return process.wait();
}

bool Process::isRunning() {
	return process.isRunning();
}

bool Process::isFailed() {
	return process.isFailed();
}

unsigned int Process::getTimeRealMS() const {
	return process.getTimeRealMS();
}

unsigned int Process::getTimeUserMS() const {
	return process.getTimeUserMS();
}

unsigned int Process::getTimeSysMS() const {
	return process.getTimeSysMS();
}

} /* namespace system */
} /* namespace esl */
