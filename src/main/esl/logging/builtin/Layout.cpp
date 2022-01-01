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

#include <esl/logging/builtin/Layout.h>
#include <esl/logging/Level.h>
#include <esl/logging/Interface.h>
#include <esl/Module.h>
#include <esl/utility/String.h>
#include <esl/Stacktrace.h>

#include <functional>
#include <time.h>
#include <ctime>
#include <stdexcept>

namespace esl {
namespace logging {
namespace builtin {

namespace {

unsigned int getLoggerThreadNo(std::thread::id threadId) {
	const logging::Interface* interface = esl::getModule().findInterface<logging::Interface>();
	return interface ? interface->getThreadNo(threadId) : static_cast<unsigned int>(std::hash<std::thread::id>{}(threadId));
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

std::string formatObject(const void* object) {
	char buffer[20];
	std::snprintf(buffer, 20, "%p", object);
	return formatStrToSize(buffer, false, 18);
}

std::string formatLineNo(unsigned int lineNo) {
	return formatStrToSize(std::to_string(lineNo),true, 6);
}

bool convertValueToBool(const std::string& value) {
	std::string normalized = utility::String::toUpper(utility::String::trim(value));
	return (normalized != "" && normalized != "0" && normalized != "NO" && normalized != "FALSE");
}

} /* anonymous namespace */

std::unique_ptr<esl::logging::layout::Interface::Layout> Layout::create(const layout::Interface::Settings& values) {
	return std::unique_ptr<esl::logging::layout::Interface::Layout>(new Layout(values));
}

Layout::Layout(const layout::Interface::Settings& settings) {
	for(const auto& setting : settings) {
		if(setting.first == "showTimestamp") {
			showTimestamp = convertValueToBool(setting.second);
		}
		else if(setting.first == "showLevel") {
			showLevel = convertValueToBool(setting.second);
		}
		else if(setting.first == "showTypeName") {
			showTypeName = convertValueToBool(setting.second);
		}
		else if(setting.first == "showAddress") {
			showAddress = convertValueToBool(setting.second);
		}
		else if(setting.first == "showFile") {
			showFile = convertValueToBool(setting.second);
		}
		else if(setting.first == "showFunction") {
			showFunction = convertValueToBool(setting.second);
		}
		else if(setting.first == "showLineNo") {
			showLineNo = convertValueToBool(setting.second);
		}
		else if(setting.first == "showThreadNo") {
			showThreadNo = convertValueToBool(setting.second);
		}
		else {
			throw esl::addStacktrace(std::runtime_error("Unknown key \"" + setting.first + "\""));
		}
	}
}

std::string Layout::toString(const Location& location) const {
	std::string rv;

	if(showTimestamp) {
		rv += formatTimestamp(location.timestamp);
	}

	if(showLevel) {
		rv += formatLevel(location.level);
	}

    rv += "(";
	if(showTypeName) {
	    rv += formatTypeName(location.typeName);
	}
	if(showThreadNo) {
		rv += "-" + formatThreadNo(getLoggerThreadNo(location.threadId));
	}
	if(showAddress) {
		rv += " @ " + formatObject(location.object);
	}
	if(showFunction) {
		rv += "|" + formatStrToSize(makeString(location.function), false, 20);
	}
	if(showFile) {
		rv += "|" + formatStrToSize(makeString(location.file), false, 20);
	}
	if(showLineNo) {
		rv += "|" + formatLineNo(location.line);
	}
	rv += "): ";

	return rv;
}

bool Layout::getShowTimestamp() const {
	return showTimestamp;
}

bool Layout::getShowLevel() const {
	return showLevel;
}

bool Layout::getShowTypeName() const {
	return showTypeName;
}

bool Layout::getShowAddress() const {
	return showAddress;
}

bool Layout::getShowFile() const {
	return showFile;
}

bool Layout::getShowFunction() const {
	return showFunction;
}

bool Layout::getShowLineNo() const {
	return showLineNo;
}

bool Layout::getShowThreadNo() const {
	return showThreadNo;
}

} /* namespace builtin */
} /* namespace logging */
} /* namespace esl */
