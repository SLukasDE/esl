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

#include <esl/io/WriterConsumer.h>
#include <esl/io/Reader.h>
#include <esl/io/ReaderStatic.h>
#include <esl/logging/Logger.h>

#include <cstring>
#include <cstdint>

namespace esl {
namespace io {

namespace {
esl::logging::Logger<> logger("esl::io::WriterConsumer");

class LocalReaderStatic : public ReaderStatic {
public:
	LocalReaderStatic(const void* data, std::size_t size)
	: ReaderStatic(data, size)
	{ }

	std::size_t read(void* data, std::size_t size) override {
		std::size_t rv = ReaderStatic::read(data, size);

		if(rv == Reader::npos && getSize() != 0) {
			return 0;
		}
		return rv;
	}
};
}

WriterConsumer::WriterConsumer(Consumer& aConsumer)
: consumer(aConsumer)
{ }

std::size_t WriterConsumer::write(const void* aData, std::size_t size) {
	const std::uint8_t* data = static_cast<const std::uint8_t*>(aData);

	if(isConsumerEOF) {
		return Writer::npos;
	}

	/* ***************************************************** *
	 * Signal consumer that no more data will be transmitted *
	 * ***************************************************** */
	if(size == 0) {
		LocalReaderStatic readerStatic(data, 0);
		isConsumerEOF = !consumer.consume(readerStatic);
		return 0;
	}


	/* *********************** *
	 * Writer data to consumer *
	 * *********************** */
	std::size_t currentPos = 0;
	while(currentPos < size) {
		std::size_t sizeRemaining = size - currentPos;
		LocalReaderStatic readerStatic(data + currentPos, sizeRemaining);
		isConsumerEOF = !consumer.consume(readerStatic);

		if(isConsumerEOF) {
			return Writer::npos;
		}

		std::size_t sizeRead = sizeRemaining - readerStatic.getSizeReadable();

		/* check if reader is stalled */
		if(sizeRead == 0) {
			break;
		}

		currentPos += sizeRead;
	}

	return currentPos;
}

// returns consumable bytes to write.
std::size_t WriterConsumer::getSizeWritable() const {
	if(isConsumerEOF) {
		return 0;
	}
	return Writer::npos;
}

} /* namespace io */
} /* namespace esl */
