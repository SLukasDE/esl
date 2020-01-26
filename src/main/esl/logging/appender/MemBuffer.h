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

#ifndef ESL_LOGGING_APPENDER_MEMBUFFER_H_
#define ESL_LOGGING_APPENDER_MEMBUFFER_H_

#include <esl/logging/Appender.h>
#include <esl/logging/Id.h>
#include <vector>
#include <string>
#include <tuple>

namespace esl {
namespace logging {
namespace appender {

class MemBuffer : public Appender {
public:
	MemBuffer(std::size_t maxRows, std::size_t maxColumns = 0);
	~MemBuffer();

	/* method is (currently) NOT thread-safe */
	std::vector<std::tuple<Id, std::string>> getBuffer() const;

protected:
	void flushNewLine(const Id& id, bool enabled) override;
	void write(const Id& id, bool enabled, const char* ptr, std::size_t size) override;

private:
    using LineBuffer = std::vector<char>;

    // this is the static buffer, used if maxColumns>0
    std::vector<LineBuffer> rows;

    // this is the dynamic buffer, used if maxColumns=0
    std::vector<std::string> lines;

    std::vector<Id> ids;

	const std::size_t maxRows;
	const std::size_t maxColumns;

	std::size_t rowProducer = 0;
	std::size_t rowConsumer = 0;
	std::size_t columnsProducer = 0;
};

} /* namespace appender */
} /* namespace logging */
} /* namespace esl */

#endif /* ESL_LOGGING_APPENDER_MEMBUFFER_H_ */