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

#include <esl/io/ProducerReader.h>
#include <esl/logging/Logger.h>

namespace esl {
namespace io {

namespace {
esl::logging::Logger<> logger("esl::io::ProducerReader");
}

constexpr std::size_t ProducerReader::maxBufferSize;

ProducerReader::ProducerReader(Reader& aReader)
: reader(aReader)
{ }

std::size_t ProducerReader::produce(Writer& writer) {
	if(isWriterEOF) {
		return Writer::npos;
	}

	if(currentBufferSize == 0 && isReaderEOF == false) {
		std::size_t consumedSize = reader.read(buffer, maxBufferSize);
		if(consumedSize == Reader::npos) {
			isReaderEOF = true;
			return Writer::npos;
		}

		if(consumedSize > maxBufferSize) {
			logger.warn << "esl::utility::io::Reader has " << consumedSize << " bytes read but only " << maxBufferSize << " bytes have been allowed to read.\n";
			consumedSize = maxBufferSize;
		}

		currentBufferSize = consumedSize;
	}

	std::size_t producedSize = 0;
	if(currentBufferSize > 0) {
		producedSize = writer.write(&buffer[maxBufferSize-currentBufferSize], currentBufferSize);

		if(producedSize == Writer::npos) {
			isWriterEOF = true;
		}
		else {
			if(producedSize > currentBufferSize) {
				logger.warn << "esl::utility::Writer has " << producedSize << " bytes written but only " << currentBufferSize << " bytes have been allwoed to write.\n";
				producedSize = currentBufferSize;
			}

			currentBufferSize -= producedSize;
		}
	}

	return producedSize;
}

Reader& ProducerReader::getReader() const noexcept {
	return reader;
}

std::size_t ProducerReader::getCurrentBufferSize() const noexcept {
	return currentBufferSize;
}

} /* namespace io */
} /* namespace esl */
