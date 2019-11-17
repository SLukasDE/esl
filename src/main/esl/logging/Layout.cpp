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

#include <esl/logging/Layout.h>
#include <esl/logging/Level.h>

#include <esl/logging/Interface.h>
#include <esl/bootstrap/Interface.h>
#include <esl/Module.h>
#include <esl/Stacktrace.h>

#include <time.h>
#include <ctime>


namespace esl {
namespace logging {

namespace {

unsigned int getLoggerThreadNo(std::thread::id threadId) {
	esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion());
	const Interface* interface = static_cast<const Interface*>(esl::getModule().getInterface(Interface::getId(), Interface::getApiVersion()));

	if(interface == nullptr) {
		throw esl::addStacktrace(std::runtime_error("no implementation available for \"esl-logging\""));
	}

	return interface->getThreadNo(threadId);
}

std::string formatStrToSize(std::string str, bool spacesAtLeftSide = false, const std::size_t strSize = 50) {
	if(str.size() > strSize) {
		str = "..." + str.substr(str.size()+3-strSize);
	}

	if(spacesAtLeftSide) {
		while(str.size() < strSize) {
			str = " " + str;
		}
	}
	else {
		while(str.size() < strSize) {
			str += " ";
		}
	}

	return str;
}

std::string makeString(const char* typeName) {
	return typeName == nullptr ? "" : typeName;
}

std::string formatTimestamp(const std::time_t& timestamp) {
    char timeStr[23];
    struct tm timeBuf;
    struct tm* timePtr;

    timePtr = localtime_r(&timestamp, &timeBuf);
    sprintf(timeStr, "$ %04d-%02d-%02d %02d:%02d:%02d ",
            timePtr->tm_year + 1900,
            timePtr->tm_mon  + 1,
            timePtr->tm_mday,
            timePtr->tm_hour,
            timePtr->tm_min,
            timePtr->tm_sec);
    return timeStr;
}

std::string formatLevel(Level level) {
    switch(level) {
    case Level::TRACE:
    	return "[TRACE] ";
    case Level::DEBUG:
    	return "[DEBUG] ";
    case Level::INFO:
    	return "[INFO ] ";
    case Level::WARN:
    	return"[WARN ] ";
    case Level::ERROR:
    	return "[ERROR] ";
    default:
        break;
    }
	return "[ n/a ] ";
}

std::string formatTypeName(const char* typeName) {
	return formatStrToSize(makeString(typeName), false, 20);
}

std::string formatThreadNo(unsigned int threadNo) {
	return formatStrToSize(std::to_string(threadNo),true, 3);
}

std::string formatObject(void* object) {
	char buffer[20];
	std::snprintf(buffer, 20, "%p", object);
	return formatStrToSize(buffer, false, 18);
}

std::string formatLineNo(unsigned int lineNo) {
	return formatStrToSize(std::to_string(lineNo),true, 6);
}

} /* anonymous namespace */




bool Layout::getShowTimestamp() const {
	return showTimestamp;
}

void Layout::setShowTimestamp(bool showTimestamp) {
	this->showTimestamp = showTimestamp;
}

bool Layout::getShowLevel() const {
	return showLevel;
}

void Layout::setShowLevel(bool showLevel) {
	this->showLevel = showLevel;
}

bool Layout::getShowTypeName() const {
	return showTypeName;
}

void Layout::setShowTypeName(bool showTypeName) {
	this->showTypeName = showTypeName;
}

bool Layout::getShowAddress() const {
	return showAddress;
}

void Layout::setShowAddress(bool showAddress) {
	this->showAddress = showAddress;
}

bool Layout::getShowFile() const {
	return showFile;
}

void Layout::setShowFile(bool showFile) {
	this->showFile = showFile;
}

bool Layout::getShowFunction() const {
	return showFunction;
}

void Layout::setShowFunction(bool showFunction) {
	this->showFunction = showFunction;
}

bool Layout::getShowLineNo() const {
	return showLineNo;
}

void Layout::setShowLineNo(bool showLineNo) {
	this->showLineNo = showLineNo;
}

bool Layout::getShowThreadNo() const {
	return showThreadNo;
}

void Layout::setShowThreadNo(bool showThreadNo) {
	this->showThreadNo = showThreadNo;
}

std::string Layout::makePrefix(const Id& id) {
	std::string rv;

	if(showTimestamp) {
		rv += formatTimestamp(id.timestamp);
	}

	if(showLevel) {
		rv += formatLevel(id.level);
	}

    rv += "(";
	if(showTypeName) {
	    rv += formatTypeName(id.typeName);
	}
	if(showThreadNo) {
		rv += "-" + formatThreadNo(getLoggerThreadNo(id.threadId));
	}
	if(showAddress) {
		rv += " @ " + formatObject(id.object);
	}
	if(showFunction) {
		rv += "|" + formatStrToSize(makeString(id.function), false, 20);
	}
	if(showFile) {
		rv += "|" + formatStrToSize(makeString(id.file), false, 20);
	}
	if(showLineNo) {
		rv += "|" + formatLineNo(id.line);
	}
	rv += "): ";

	return rv;
}

} /* namespace logging */
} /* namespace esl */
