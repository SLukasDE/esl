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

#ifndef ESL_SYSTEM_PROCESS_PROCESS_H_
#define ESL_SYSTEM_PROCESS_PROCESS_H_

#include <esl/system/process/Interface.h>
#include <esl/system/process/Transceiver.h>
#include <esl/system/process/Arguments.h>
#include <esl/system/process/Environment.h>
#include <esl/system/process/FileDescriptor.h>
#include <esl/module/Implementation.h>
#include <esl/system/SignalType.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace esl {
namespace system {
namespace process {

class Process final : public Interface::Process {
public:
	static module::Implementation& getDefault();

	Process(const std::vector<std::pair<std::string, std::string>>& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());

	Transceiver& operator[](const FileDescriptor& fd) override;

	void setWorkingDir(std::string workingDir) override;
	void setEnvironment(std::unique_ptr<Environment> environment) override;
	const Environment* getEnvironment() const override;

	void addFeature(object::Interface::Object& feature) override;

	void sendSignal(SignalType signal) const override;
	const void* getNativeHandle() const override;

	int execute(Arguments arguments) const override;

private:
	std::unique_ptr<Interface::Process> process;
};

} /* namespace process */
} /* namespace system */
} /* namespace esl */

#endif /* ESL_SYSTEM_PROCESS_PROCESS_H_ */
