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

#include <esl/io/Output.h>
#include <esl/io/ProducerReader.h>
#include <esl/io/ReaderProducer.h>
#include <esl/Stacktrace.h>

#include <stdexcept>

namespace esl {
namespace io {

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


Output::Output(std::unique_ptr<Reader> aReaderGenerated)
: producerGenerated(aReaderGenerated ? new ProducerReader(*aReaderGenerated) : nullptr),
  readerGenerated(std::move(aReaderGenerated)),
  producer(producerGenerated.get()),
  reader(readerGenerated.get())
{ }

Output::Output(std::unique_ptr<Producer> aProducerGenerated)
: producerGenerated(std::move(aProducerGenerated)),
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
        throw esl::addStacktrace(std::runtime_error("calling Output::getProducer() but object is empty."));
	}
	return *producer;
}

Reader& Output::getReader() const noexcept {
	if(reader == nullptr) {
        throw esl::addStacktrace(std::runtime_error("calling Output::getReader() but object is empty."));
	}
	return *reader;
}

} /* namespace io */
} /* namespace esl */
