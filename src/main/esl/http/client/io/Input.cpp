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

#include <esl/http/client/io/Input.h>
#include <esl/http/client/io/ConsumerWriter.h>
#include <esl/http/client/io/WriterConsumer.h>
#include <esl/http/client/io/IOConsumer.h>
#include <esl/http/client/io/IOWriter.h>
#include <esl/Stacktrace.h>

#include <stdexcept>

namespace esl {
namespace http {
namespace client {
namespace io {

Input::Input(Writer& aWriter)
: consumerGenerated(new ConsumerWriter(aWriter)),
  consumer(consumerGenerated.get()),
  writer(&aWriter)
{ }

Input::Input(Consumer& aConsumer)
: writerGenerated(new WriterConsumer(aConsumer)),
  consumer(&aConsumer),
  writer(writerGenerated.get())
{ }

Input::Input(esl::io::Input&& other)
: ioInput(std::move(other)),
  consumerGenerated(new IOConsumer(ioInput.getConsumer())),
  writerGenerated(new IOWriter(ioInput.getWriter())),
  consumer(consumerGenerated.get()),
  writer(writerGenerated.get())
{ }

Input::Input(Input&& other)
: consumerGenerated(std::move(other.consumerGenerated)),
  writerGenerated(std::move(other.writerGenerated)),
  consumer(other.consumer),
  writer(other.writer)
{
	other.consumer = nullptr;
	other.writer = nullptr;
}

Input& Input::operator=(Input&& other) {
	if(this != &other) {
		ioInput = std::move(other.ioInput);

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
        throw esl::addStacktrace(std::runtime_error("calling esl::http::client::io::Input::getConsumer() but object is empty."));
	}
	return *consumer;
}

Writer& Input::getWriter() const {
	if(writer == nullptr) {
        throw esl::addStacktrace(std::runtime_error("calling esl::http::client::io::Input::getWriter() but object is empty."));
	}
	return *writer;
}

} /* namespace io */
} /* namespace client */
} /* namespace http */
} /* namespace esl */
