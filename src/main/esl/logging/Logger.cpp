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

#include <esl/logging/Logger.h>
#include <esl/logging/Appender.h>

#include <esl/logging/Interface.h>
#include <esl/bootstrap/Interface.h>
#include <esl/Module.h>
#include <esl/Stacktrace.h>

namespace esl {
namespace logging {

namespace {

void setLoggerUnblocked(bool isUnblocked) {
	esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion());
	const Interface* interface = static_cast<const Interface*>(esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion()));

	if(interface == nullptr) {
		throw esl::addStacktrace(std::runtime_error("no implementation available for \"esl-logging\""));
	}

	interface->setUnblocked(isUnblocked);
}

void setLoggerLevel(Level logLevel, const std::string& typeName) {
	esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion());
	const Interface* interface = static_cast<const Interface*>(esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion()));

	if(interface == nullptr) {
		throw esl::addStacktrace(std::runtime_error("no implementation available for \"esl-logging\""));
	}

	interface->setLevel(logLevel, typeName);
}

void addLoggerAppender(Appender& appender) {
	esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion());
	const Interface* interface = static_cast<const Interface*>(esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion()));

	if(interface == nullptr) {
		throw esl::addStacktrace(std::runtime_error("no implementation available for \"esl-logging\""));
	}

	interface->addAppender(appender);
}

std::vector<std::reference_wrapper<Appender>> getLoggerAppenders() {
	esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion());
	const Interface* interface = static_cast<const Interface*>(esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion()));

	if(interface == nullptr) {
		throw esl::addStacktrace(std::runtime_error("no implementation available for \"esl-logging\""));
	}

	return interface->getAppenders();
}


unsigned int getLoggerThreadNo(std::thread::id threadId) {
	esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion());
	const Interface* interface = static_cast<const Interface*>(esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion()));

	if(interface == nullptr) {
		throw esl::addStacktrace(std::runtime_error("no implementation available for \"esl-logging\""));
	}

	return interface->getThreadNo(threadId);
}

}

Logger::Logger(const char* aTypeName)
: trace(aTypeName, Level::TRACE),
  debug(aTypeName, Level::DEBUG),
  info(aTypeName, Level::INFO),
  warn(aTypeName, Level::WARN),
  error(aTypeName, Level::ERROR),
  typeName(aTypeName)
{
}

void Logger::setUnblocked(bool isUnblocked) {
	setLoggerUnblocked(isUnblocked);
}

void Logger::setLevel(Level logLevel) {
	setLevel(logLevel, typeName);
}

void Logger::setLevel(Level logLevel, const std::string& typeName) {
	setLoggerLevel(logLevel, typeName);
}

void Logger::addAppender(Appender& appender) {
	addLoggerAppender(appender);
}

std::vector<std::reference_wrapper<Appender>> Logger::getAppenders() {
	return getLoggerAppenders();
}

} /* namespace logging */

esl::logging::Logger logger("esl");

} /* namespace esl */


