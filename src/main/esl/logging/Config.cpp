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

#include <esl/logging/Config.h>
#include <esl/logging/ILogger.h>
#include <esl/plugin/Plugin.h>
#include <esl/plugin/Registry.h>

#include <memory>

namespace esl {
namespace logging {

namespace {
class DummyLogger : public ILogger {
public:
	void setUnblocked(bool isUnblocked) override {
	}

	void setLevel(Level logLevel, const std::string& typeName) override {
	}

	void* addAppender(IAppender& appender) override {
		return nullptr;
	}

	void removeAppender(void* handle) override {
	}

	bool isEnabled(const char* typeName, Level level) override {
		return false;
	}

	std::unique_ptr<OStream> createOStream(const Location& location) override {
		return nullptr;
	}

	unsigned int getThreadNo(std::thread::id threadId) override {
		return static_cast<unsigned int>(std::hash<std::thread::id>{}(threadId));
	}
};

ILogger& getLogger() {
	static ILogger* iLogger = nullptr;
	static DummyLogger dummyLogger;

	if(iLogger == nullptr) {
		const ILogger::Plugin* loggerPlugin = plugin::Registry::get().findPlugin<ILogger::Plugin>();
		if(loggerPlugin) {
			iLogger = loggerPlugin->create({}).release();
		}
	}

	return iLogger ? *iLogger : dummyLogger;
}
} /* anonymous namespace */

IAppender::~IAppender() {
	getLogger().removeAppender(handle);
}

void Config::setUnblocked(bool isUnblocked) {
	getLogger().setUnblocked(isUnblocked);
}

void Config::setLevel(Level logLevel, const std::string& typeName) {
	getLogger().setLevel(logLevel, typeName);
}

void Config::addAppender(IAppender& appender) {
	/* we are done if appender has been already added */
	if(appender.handle != nullptr) {
		return;
	}

	getLogger().addAppender(appender);
}

bool Config::isEnabled(const char* typeName, Level level) {
	return getLogger().isEnabled(typeName, level);
}

std::unique_ptr<OStream> Config::createOStream(const Location& location) {
	return getLogger().createOStream(location);
}

unsigned int Config::getThreadNo(std::thread::id threadId) {
	return getLogger().getThreadNo(threadId);
}

} /* namespace logging */
} /* namespace esl */
