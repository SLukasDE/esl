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

#include <esl/io/Output.h>
#include <esl/io/Writer.h>
#include <esl/logging/Logger.h>

#include <string>
#include <stdexcept>
#include <cstdint>
#include <cstring>

namespace esl {
namespace io {

namespace {
logging::Logger<> logger("esl::io::Output");

class ProducerReader : public Producer {
public:
	ProducerReader(Reader& reader);

	std::size_t produce(Writer& writer) override;

	Reader& getReader() const noexcept;
	std::size_t getCurrentBufferSize() const noexcept;

private:
	static constexpr std::size_t maxBufferSize = 4096;
	std::size_t currentBufferSize = 0;
	char buffer[maxBufferSize];
	Reader& reader;
	bool isReaderEOF = false;
	bool isWriterEOF = false;
};

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
			logger.warn << "esl::io::Output-ProducerReader::produce has " << consumedSize << " bytes read but only " << maxBufferSize << " bytes have been allowed to read.\n";
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
				logger.warn << "esl::io::Output-ProducerReader::produce has " << producedSize << " bytes written but only " << currentBufferSize << " bytes have been allwoed to write.\n";
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




class WriterMemory : public Writer {
public:
	WriterMemory(void* data, std::size_t size);

	std::size_t write(const void* data, std::size_t size) override;

	// returns consumable bytes to write.
	// npos is returned if available size is unknown.
	std::size_t getSizeWritable() const override;

private:
	void* bufferData;
	std::size_t bufferSize;
	std::size_t currentPos = 0;
};

WriterMemory::WriterMemory(void* data, std::size_t size)
: bufferData(data),
  bufferSize(size)
{ }

std::size_t WriterMemory::write(const void* data, std::size_t size) {
	if(bufferSize == 0) {
		return Writer::npos;
	}

	if(size > getSizeWritable()) {
		size = getSizeWritable();
	}

	if(size > 0) {
		std::memcpy(static_cast<char*>(bufferData) + currentPos, data, size);
		currentPos += size;
	}

	return size;
}

// returns consumable bytes to write.
// npos is returned if available size is unknown.
std::size_t WriterMemory::getSizeWritable() const {
	return bufferSize - currentPos;
}




class ReaderProducer : public Reader {
public:
	ReaderProducer(Producer& producer);

	std::size_t read(void* data, std::size_t size) override;
	std::size_t getSizeReadable() const override;
	bool hasSize() const override;
	std::size_t getSize() const override;

private:
	Producer& producer;
	bool isProducerEOF = false;
};

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
		WriterMemory writerStatic(data, 0);
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
		WriterMemory writerStatic(data + currentPos, sizeRemaining);
		isProducerEOF = (producer.produce(writerStatic) == Writer::npos);

		if(isProducerEOF) {
			break;
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

} /* anonymous namespace */

Output::Output(Reader& aReader)
: producerGenerated(new ProducerReader(aReader)),
  producer(producerGenerated.get()),
  reader(&aReader)
{ }

Output::Output(Producer& aProducer)
: readerGenerated(new ReaderProducer(aProducer)),
  producer(&aProducer),
  reader(readerGenerated.get())
{ }


Output::Output(std::unique_ptr<Reader> aReader)
: producerGenerated(aReader ? new ProducerReader(*aReader) : nullptr),
  readerGenerated(std::move(aReader)),
  producer(producerGenerated.get()),
  reader(readerGenerated.get())
{ }

Output::Output(std::unique_ptr<Producer> aProducer)
: producerGenerated(std::move(aProducer)),
  readerGenerated(producerGenerated ? new ReaderProducer(*producerGenerated) : nullptr),
  producer(producerGenerated.get()),
  reader(readerGenerated.get())
{ }

Output::Output(Output&& other)
: producerGenerated(std::move(other.producerGenerated)),
  readerGenerated(std::move(other.readerGenerated)),
  producer(other.producer),
  reader(other.reader)
{
	other.producer = nullptr;
	other.reader = nullptr;
}

Output& Output::operator=(Output&& other) {
	if(this != &other) {
		producerGenerated = std::move(other.producerGenerated);
		readerGenerated = std::move(other.readerGenerated);

		producer = other.producer;
		other.producer = nullptr;

		reader = other.reader;
		other.reader = nullptr;
	}

	return *this;
}

Output::operator bool() const noexcept {
	return producer != nullptr && reader != nullptr;
}

Producer& Output::getProducer() const noexcept {
	if(producer == nullptr) {
        throw std::runtime_error("calling Output::getProducer() but object is empty.");
	}
	return *producer;
}

Reader& Output::getReader() const noexcept {
	if(reader == nullptr) {
        throw std::runtime_error("calling Output::getReader() but object is empty.");
	}
	return *reader;
}

} /* namespace io */
} /* namespace esl */
