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

#include <esl/io/ReaderProducer.h>
#include <esl/io/Writer.h>
#include <esl/io/WriterStatic.h>

#include <cstdint>

namespace esl {
namespace io {

namespace {
class LocalWriterStatic : public WriterStatic {
public:
	LocalWriterStatic(void* data, std::size_t size)
	: WriterStatic(data, size)
	{ }

	std::size_t write(const void* data, std::size_t size) override {
		std::size_t rv = WriterStatic::write(data, size);

		if(rv == Reader::npos && getSizeWritable() != 0) {
			return 0;
		}
		return rv;
	}
};
}

ReaderProducer::ReaderProducer(Producer& aProducer)
: producer(aProducer)
{ }

std::size_t ReaderProducer::read(void* aData, std::size_t size) {
	std::uint8_t* data = static_cast<std::uint8_t*>(aData);

	if(isProducerEOF) {
		return Reader::npos;
	}

	/* ************************************************** *
	 * Signal producer that no more data will be received *
	 * ************************************************** */
	if(size == 0) {
		LocalWriterStatic writerStatic(data, 0);
		producer.produce(writerStatic);
		isProducerEOF = true;
		return 0;
	}


	/* ********************* *
	 * Read data from reader *
	 * ********************* */
	std::size_t currentPos = 0;
	while(currentPos < size) {
		std::size_t sizeRemaining = size - currentPos;
		LocalWriterStatic writerStatic(data + currentPos, sizeRemaining);
		isProducerEOF = (producer.produce(writerStatic) == Writer::npos);

		if(isProducerEOF) {
			return Reader::npos;
		}

		std::size_t sizeWritten = sizeRemaining - writerStatic.getSizeWritable();

		/* check if writer is stalled */
		if(sizeWritten == 0) {
			break;
		}

		currentPos += sizeWritten;
	}

	return currentPos;
}

// returns available bytes that can be read with next call of read(...).
// npos is returned if available size is unknown.
// 0 just means, that there are currently no bytes available and read() would return as well 0.
// 0 does NOT mean, that there are no more bytes available in general. This you will know by calling read(...)
std::size_t ReaderProducer::getSizeReadable() const {
	return Reader::npos;
}

bool ReaderProducer::hasSize() const {
	return false;
}

std::size_t ReaderProducer::getSize() const {
	return Reader::npos;
}

} /* namespace io */
} /* namespace esl */
