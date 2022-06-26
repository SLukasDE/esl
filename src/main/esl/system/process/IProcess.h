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

#ifndef ESL_SYSTEM_PROCESS_IPROCESS_H_
#define ESL_SYSTEM_PROCESS_IPROCESS_H_

#include <esl/system/process/Transceiver.h>
#include <esl/system/process/Arguments.h>
#include <esl/system/process/Environment.h>
#include <esl/system/process/FileDescriptor.h>
#include <esl/object/IObject.h>
#include <esl/plugin/Plugin.h>
#include <esl/utility/Signal.h>

#include <memory>
#include <string>


namespace esl {
namespace system {
namespace process {

class IProcess : public object::IObject {
public:
	using Plugin = plugin::Plugin<IProcess>;

	IProcess() = default;

	virtual Transceiver& operator[](const FileDescriptor& fd) = 0;

	virtual void setWorkingDir(std::string workingDir) = 0;
	virtual void setEnvironment(std::unique_ptr<Environment> environment) = 0;
	virtual const Environment* getEnvironment() const = 0;

	virtual void addFeature(object::IObject& feature) = 0;

	virtual int execute(Arguments arguments) const = 0;

	virtual void sendSignal(const utility::Signal& signal) const = 0;
	virtual const void* getNativeHandle() const = 0;
};

} /* namespace process */
} /* namespace system */
} /* namespace esl */

#endif /* ESL_SYSTEM_PROCESS_IPROCESS_H_ */
