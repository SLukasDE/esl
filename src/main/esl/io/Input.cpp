/*
MIT License
Copyright (c) 2019-2025 Sven Lukas

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

#include <esl/io/Input.h>
#include <esl/io/Reader.h>
#include <esl/monitoring/Logger.h>
#include <esl/monitoring/Streams.h>

#include <string>
#include <stdexcept>
#include <cstdint>
#include <cstring>

namespace esl {
inline namespace v1_6 {
namespace io {

namespace {
monitoring::Logger<monitoring::Streams::Level::trace> logger("esl::io::Input");

class ConsumerWriter : public Consumer {
public:
	ConsumerWriter(Writer& writer);

	bool consume(Reader& reader) override;

#ifdef ESL_1_6
private:
	/* return true on progress - maybe call method again */
	bool flushBuffer();

#else
	Writer& getWriter() const noexcept;
	std::size_t getCurrentBufferSize() const noexcept;
	void flushBuffer();

private:
#endif
	static constexpr std::size_t maxBufferSize = 4096;
	std::size_t currentBufferSize = 0;
#ifdef ESL_1_6
	std::size_t flushedBufferSize = 0;
#endif
	char buffer[maxBufferSize];
	Writer& writer;
	bool isReaderEOF = false;
	bool isWriterEOF = false;
};

constexpr std::size_t ConsumerWriter::maxBufferSize;

ConsumerWriter::ConsumerWriter(Writer& aWriter)
: writer(aWriter)
{ }

#ifdef ESL_1_6
bool ConsumerWriter::consume(Reader& reader) {
	while(flushBuffer()) {
	}

	if(isWriterEOF) {
		return false;
	}

	if(currentBufferSize == 0 && isReaderEOF == false) {
		std::size_t consumedSize = reader.read(buffer, maxBufferSize);

		if(consumedSize == Reader::npos) {
			isReaderEOF = true;
			return false;
		}

		if(consumedSize > maxBufferSize) {
			logger.warn << "esl::io::Input-ConsumerWriter::consume says " << consumedSize << " bytes read but read at most " << maxBufferSize << " bytes.\n";
			consumedSize = maxBufferSize;
		}

		currentBufferSize = consumedSize;
	}

	while(flushBuffer()) {
	}

	return isWriterEOF == false && (isReaderEOF == false || currentBufferSize > 0);
}

bool ConsumerWriter::flushBuffer() {
	if(currentBufferSize == 0 || isWriterEOF) {
		return false;
	}

	std::size_t producedSize = writer.write(&buffer[flushedBufferSize], currentBufferSize-flushedBufferSize);

	if(producedSize == Writer::npos) {
		isWriterEOF = true;
		return false;
	}

	if(producedSize > currentBufferSize) {
		logger.warn << "esl::io::Input-ConsumerWriter::flushBuffer has " << producedSize << " bytes written but only " << currentBufferSize-flushedBufferSize << " bytes have been allowed to write.\n";
		producedSize = currentBufferSize;
	}

	flushedBufferSize += producedSize;

	if(flushedBufferSize < currentBufferSize) {
		return (producedSize > 0);
	}
	if(flushedBufferSize > currentBufferSize) {
		logger.warn << "esl::io::Input-ConsumerWriter::flushBuffer has " << flushedBufferSize << " bytes totaly written but only " << currentBufferSize << " bytes totaly have been allowed to write.\n";
	}

	currentBufferSize = 0;
	flushedBufferSize = 0;

	return true;
}
#else
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
				logger.warn << "esl::io::Input-ConsumerWriter::consume says " << consumedSize << " bytes read but read at most " << maxBufferSize << " bytes.\n";
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
			logger.warn << "esl::io::Input-ConsumerWriter::flushBuffer has " << producedSize << " bytes written but only " << currentBufferSize << " bytes have been allowed to write.\n";
			producedSize = currentBufferSize;
		}

		currentBufferSize -= producedSize;
	}
}
#endif




class ReaderMemory : public Reader {
public:
	ReaderMemory(const void* data, std::size_t size);

	std::size_t read(void* data, std::size_t size) override;
	std::size_t getSizeReadable() const override;
	bool hasSize() const override;
	std::size_t getSize() const override;

private:
	const void* getData() const noexcept;

	const void* data;
	std::size_t size;
	std::size_t currentPos = 0;
};

ReaderMemory::ReaderMemory(const void* aData, std::size_t aSize)
: data(aData),
  size(aSize)
{ }

std::size_t ReaderMemory::read(void* data, std::size_t size) {
	if(currentPos >= getSize()) {
		return getSize() == 0 ? Reader::npos : 0;
	}

	if(size > getSizeReadable()) {
		size = getSizeReadable();
	}

	std::memcpy(data, static_cast<const char*>(getData()) + currentPos, size);
	currentPos += size;

	return size;
}

std::size_t ReaderMemory::getSizeReadable() const {
	if(currentPos >= getSize()) {
		return 0;
	}

	return getSize() - currentPos;
}

bool ReaderMemory::hasSize() const {
	return true;
}

std::size_t ReaderMemory::getSize() const {
	return size;
}

const void* ReaderMemory::getData() const noexcept {
	return data;
}



class WriterConsumer : public Writer {
public:
	WriterConsumer(Consumer& consumer);

	std::size_t write(const void* data, std::size_t size) override;

	// returns consumable bytes to write.
	// npos is returned if available size is unknown.
	// Here: It's only npos returned or 0 if Consumer::consume returned false
	std::size_t getSizeWritable() const override;

private:
	Consumer& consumer;
	bool isConsumerEOF = false;
};


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
		ReaderMemory readerStatic(data, 0);
		isConsumerEOF = !consumer.consume(readerStatic);
		return 0;
	}


	/* *********************** *
	 * Writer data to consumer *
	 * *********************** */
	std::size_t currentPos = 0;
	while(currentPos < size) {
		std::size_t sizeRemaining = size - currentPos;
		ReaderMemory readerStatic(data + currentPos, sizeRemaining);
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

}

Input::Input(std::unique_ptr<object::Object> aObject, Consumer& aConsumer, Writer& aWriter)
: object(std::move(aObject)),
  consumer(&aConsumer),
  writer(&aWriter)
{ }

Input::Input(Consumer& aConsumer)
: writerGenerated(new WriterConsumer(aConsumer)),
  consumer(&aConsumer),
  writer(writerGenerated.get())
{ }

Input::Input(Writer& aWriter)
: consumerGenerated(new ConsumerWriter(aWriter)),
  consumer(consumerGenerated.get()),
  writer(&aWriter)
{ }

Input::Input(std::unique_ptr<Consumer> aConsumerGenerated)
: consumerGenerated(std::move(aConsumerGenerated)),
  writerGenerated(consumerGenerated ? new WriterConsumer(*consumerGenerated) : nullptr),
  consumer(consumerGenerated.get()),
  writer(writerGenerated.get())
{ }

Input::Input(std::unique_ptr<Writer> aWriterGenerated)
: consumerGenerated(aWriterGenerated ? new ConsumerWriter(*aWriterGenerated) : nullptr),
  writerGenerated(std::move(aWriterGenerated)),
  consumer(consumerGenerated.get()),
  writer(writerGenerated.get())
{ }

Input::Input(Input&& other)
: object(std::move(other.object)),
  consumerGenerated(std::move(other.consumerGenerated)),
  writerGenerated(std::move(other.writerGenerated)),
  consumer(other.consumer),
  writer(other.writer)
{
	other.consumer = nullptr;
	other.writer = nullptr;
}

Input& Input::operator=(Input&& other) {
	if(this != &other) {
		object = std::move(other.object);

		consumerGenerated = std::move(other.consumerGenerated);
		writerGenerated = std::move(other.writerGenerated);

		consumer = other.consumer;
		other.consumer = nullptr;

		writer = other.writer;
		other.writer = nullptr;
	}

	return *this;
}

Input::operator bool() const noexcept {
	return consumer != nullptr && writer != nullptr;
}

Consumer& Input::getConsumer() const {
	if(consumer == nullptr) {
        throw std::runtime_error("calling esl::io::Input::getConsumer() but object is empty.");
	}
	return *consumer;
}

Writer& Input::getWriter() const {
	if(writer == nullptr) {
        throw std::runtime_error("calling esl::io::Input::getWriter() but object is empty.");
	}
	return *writer;
}

} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */
