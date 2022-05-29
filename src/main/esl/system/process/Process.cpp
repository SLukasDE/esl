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

#include <esl/system/process/Process.h>
#include <esl/Module.h>

namespace esl {
namespace system {
namespace process {

module::Implementation& Process::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

Process::Process(const std::vector<std::pair<std::string, std::string>>& settings, const std::string& implementation)
: process(getModule().getInterface<Interface>(implementation).createProcess(settings))
{ }

Transceiver& Process::operator[](const FileDescriptor& fd) {
	return (*process)[fd];
}

void Process::setWorkingDir(std::string workingDir) {
	process->setWorkingDir(std::move(workingDir));
}

void Process::setEnvironment(std::unique_ptr<Environment> environment) {
	process->setEnvironment(std::move(environment));
}

const Environment* Process::getEnvironment() const {
	return process->getEnvironment();
}

void Process::addFeature(object::Interface::Object& feature) {
	return process->addFeature(feature);
}

void Process::sendSignal(const utility::Signal& signal) const {
	process->sendSignal(signal);
}

const void* Process::getNativeHandle() const {
	return process->getNativeHandle();
}

int Process::execute(Arguments arguments) const {
	return process->execute(std::move(arguments));
}

} /* namespace process */
} /* namespace system */
} /* namespace esl */
