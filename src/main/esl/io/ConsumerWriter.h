/*
MIT License
Copyright (c) 2019-2021 Sven Lukas

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

#ifndef ESL_IO_CONSUMERWRITER_H_
#define ESL_IO_CONSUMERWRITER_H_

#include <esl/io/Consumer.h>
#include <esl/io/Reader.h>
#include <esl/io/Writer.h>

#include <string>

namespace esl {
namespace io {

class ConsumerWriter : public Consumer {
public:
	ConsumerWriter(Writer& writer);

	bool consume(Reader& reader) override;

	Writer& getWriter() const noexcept;
	std::size_t getCurrentBufferSize() const noexcept;
	void flushBuffer();

private:
	static constexpr std::size_t maxBufferSize = 4096;
	std::size_t currentBufferSize = 0;
	char buffer[maxBufferSize];
	Writer& writer;
	bool isReaderEOF = false;
	bool isWriterEOF = false;
};

} /* namespace io */
} /* namespace esl */

#endif /* ESL_IO_CONSUMERWRITER_H_ */
