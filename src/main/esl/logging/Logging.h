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

#ifndef ESL_LOGGING_LOGGING_H_
#define ESL_LOGGING_LOGGING_H_

#include <esl/object/Object.h>
#include <esl/logging/Appender.h>
#include <esl/logging/Layout.h>
#include <esl/logging/Level.h>
#include <esl/logging/Location.h>
#include <esl/logging/OStream.h>
#include <esl/logging/StreamReal.h>

#include <boost/filesystem/path.hpp>

#include <memory>
#include <ostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

namespace esl {
namespace logging {

class Logging : public esl::object::Object {
public:
	// NOT thread save - call it at the beginning if needed. Default is already "true"
	// unblocked behavior makes other threads not waiting on logging, while current thread is writing to logger already.
	// If logger is used already by current thread, other threads will write to a temporary buffer.
	// - Temporary buffer is flushed to real logger, if other thread is done using the logger.
	// - If logger is still used by current thread, buffer is queued.
	// - If current thread is done using the logger, it flushes queued buffers.
	virtual void setUnblocked(bool isUnblocked) = 0;

	// thread safe
	virtual void setLevel(Level logLevel, const std::string& typeName) = 0;

	virtual bool isEnabled(const char* typeName, Level level) = 0;
	virtual std::unique_ptr<OStream> createOStream(const Location& location) = 0;
	virtual unsigned int getThreadNo(std::thread::id threadId) = 0;

	virtual void flush(std::ostream* oStream) = 0;

	virtual void addData(const std::string& configuration) = 0;
	virtual void addFile(const boost::filesystem::path& filename) = 0;

	virtual void addLayout(const std::string& id, std::unique_ptr<Layout> layout) = 0;

	// thread safe
	virtual void addAppender(const std::string& name, const std::string& layoutRefId, std::unique_ptr<Appender> appender) = 0;

	static void init();
	static void init(std::unique_ptr<Logging> logging);
	static void init(const std::string& implementation, const std::vector<std::pair<std::string, std::string>>& settings);

	static void initWithData(const std::string& configuration);
	static void initWithData(const std::string& configuration, std::unique_ptr<Logging> logging);
	static void initWithData(const std::string& configuration, const std::string& implementation, const std::vector<std::pair<std::string, std::string>>& settings);

	static void initWithFile(const boost::filesystem::path& filename);
	static void initWithFile(const boost::filesystem::path& filename, std::unique_ptr<Logging> logging);
	static void initWithFile(const boost::filesystem::path& filename, const std::string& implementation, const std::vector<std::pair<std::string, std::string>>& settings);

	static Logging* get();
};

} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_LOGGING_H_ */
