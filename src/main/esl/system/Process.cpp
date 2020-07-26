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

#include <esl/system/Process.h>
#include <esl/Module.h>

namespace esl {
namespace system {
namespace {
std::string defaultImplementation;
}

void Process::setDefaultImplementation(std::string implementation) {
	defaultImplementation = std::move(implementation);
}

const std::string& Process::getDefaultImplementation() {
	return defaultImplementation;
}

Process::Process(process::Arguments arguments, std::string workingDir, const std::string& implementation)
: process(esl::getModule().getInterface<Interface>(implementation).createProcess(std::move(arguments), std::move(workingDir)))
{ }

Process::Process(process::Arguments arguments, process::Environment environment, std::string workingDir, const std::string& implementation)
: process(esl::getModule().getInterface<Interface>(implementation).createProcessWithEnvironment(std::move(arguments), std::move(environment), std::move(workingDir)))
{ }

int Process::execute() {
	ParameterFeatures parameterFeatures;

	return execute(ParameterStreams(), parameterFeatures);
}

int Process::execute(Interface::FileDescriptor::Handle handle) {
	ParameterStreams parameterStream;
	ParameterFeatures parameterFeatures;

	addParameterStream(parameterStream, handle, nullptr, nullptr);
	return execute(parameterStream, parameterFeatures);
}

int Process::execute(Interface::Producer& producer, Interface::FileDescriptor::Handle handle) {
	ParameterStreams parameterStream;
	ParameterFeatures parameterFeatures;

	addParameterStream(parameterStream, handle, &producer, nullptr);
	return execute(parameterStream, parameterFeatures);
}

int Process::execute(Interface::Consumer& consumer, Interface::FileDescriptor::Handle handle) {
	ParameterStreams parameterStream;
	ParameterFeatures parameterFeatures;

	addParameterStream(parameterStream, handle, nullptr, &consumer);
	return execute(parameterStream, parameterFeatures);
}

int Process::execute(Interface::Feature& feature) {
	ParameterFeatures parameterFeatures;

	parameterFeatures.emplace_back(std::ref(feature));
	return execute(ParameterStreams(), parameterFeatures);
}

int Process::execute(const ParameterStreams& parameterStreams, ParameterFeatures& parameterFeatures) {
	return process->execute(parameterStreams, parameterFeatures);
}

void Process::addParameterStream(ParameterStreams& parameterStreams, Interface::FileDescriptor::Handle handle, Interface::Producer* producer, Interface::Consumer* consumer) {
	ParameterStream& parameterStream = parameterStreams[handle];

	if(producer == nullptr && consumer == nullptr) {
    	if(parameterStream.producer && parameterStream.consumer) {
    		throw esl::addStacktrace(std::runtime_error("Conflicting parameters: Flag defined to close handle " + std::to_string(handle) + " for child process, but there is already a producer and a consumer defined for this handle."));
    	}
    	else if(parameterStream.producer && parameterStream.consumer == nullptr) {
    		throw esl::addStacktrace(std::runtime_error("Conflicting parameters: Flag defined to close handle " + std::to_string(handle) + " for child process, but there is already a producer defined for this handle."));
    	}
    	else if(parameterStream.producer == nullptr && parameterStream.consumer) {
    		throw esl::addStacktrace(std::runtime_error("Conflicting parameters: Flag defined to close handle " + std::to_string(handle) + " for child process, but there is already a consumer defined for this handle."));
    	}
	}
	else {
    	if(producer) {
        	if(parameterStream.producer) {
        		throw esl::addStacktrace(std::runtime_error("Conflicting parameters: Multiple producer defined for handle " + std::to_string(handle) + " for child process."));
        	}
        	parameterStream.producer = producer;
    	}

    	if(consumer) {
        	if(parameterStream.consumer) {
        		throw esl::addStacktrace(std::runtime_error("Conflicting parameters: Multiple producer defined for handle " + std::to_string(handle) + " for child process."));
        	}
        	parameterStream.consumer = consumer;
    	}
	}
}

} /* namespace system */
} /* namespace esl */
