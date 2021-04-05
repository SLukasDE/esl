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

#include <esl/io/ConsumerWriter.h>
#include <esl/logging/Logger.h>

namespace esl {
namespace io {

namespace {
esl::logging::Logger<> logger("esl::io::ConsumerWriter");
}

constexpr std::size_t ConsumerWriter::maxBufferSize;

ConsumerWriter::ConsumerWriter(Writer& aWriter)
: writer(aWriter)
{ }

bool ConsumerWriter::consume(Reader& reader) {
	if(isWriterEOF) {
		return false;
	}

	if(currentBufferSize == 0 && isReaderEOF == false) {
		std::size_t consumedSize = reader.read(buffer, maxBufferSize);

		if(consumedSize == Reader::npos) {
			isReaderEOF = true;
		}
		else {
			if(consumedSize > maxBufferSize) {
				logger.warn << "esl::utility::Reader says " << consumedSize << " bytes read but read at most " << maxBufferSize << " bytes.\n";
				consumedSize = maxBufferSize;
			}

			currentBufferSize = consumedSize;
		}
	}

	flushBuffer();

	return isWriterEOF == false && (isReaderEOF == false || currentBufferSize > 0);
}

Writer& ConsumerWriter::getWriter() const noexcept {
	return writer;
}

std::size_t ConsumerWriter::getCurrentBufferSize() const noexcept {
	return currentBufferSize;
}

void ConsumerWriter::flushBuffer() {
	if(currentBufferSize > 0 && isWriterEOF == false) {
		std::size_t producedSize = writer.write(&buffer[maxBufferSize-currentBufferSize], currentBufferSize);

		if(producedSize == Writer::npos) {
			isWriterEOF = true;
			return;
		}

		if(producedSize > currentBufferSize) {
			logger.warn << "esl::utility::Writer has " << producedSize << " bytes written but only " << currentBufferSize << " bytes have been allowed to write.\n";
			producedSize = currentBufferSize;
		}

		currentBufferSize -= producedSize;
	}
}

} /* namespace io */
} /* namespace esl */
