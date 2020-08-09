/*
MIT License
Copyright (c) 2019, 2020 Sven Lukas

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

#include <esl/system/process/ConsumerWriter.h>
#include <esl/object/ValueSettings.h>
#include <esl/logging/Logger.h>

namespace esl {
namespace system {
namespace process {
namespace {
esl::logging::Logger<> logger("esl::system::process::ConsumerWriter");
}

module::Implementation& ConsumerWriter::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

ConsumerWriter::ConsumerWriter(utility::Writer& aWriter,
		std::initializer_list<std::pair<std::string, std::string>> settings,
		const std::string& implementation)
: writer(&aWriter)
{ }

ConsumerWriter::ConsumerWriter(utility::Writer& aWriter,
		const object::Values<std::string>& settings,
		const std::string& implementation)
: writer(&aWriter)
{ }

std::size_t ConsumerWriter::read(utility::Reader& reader) {
	std::size_t consumedSize = 0;

	if(currentBufferSize == 0) {
		consumedSize = reader.read(buffer, maxBufferSize);
		if(consumedSize != utility::Reader::npos) {
			if(consumedSize > maxBufferSize) {
				logger.warn << "esl::utility::Reader says " << consumedSize << " bytes read but read at most " << maxBufferSize << " bytes.\n";
				consumedSize = maxBufferSize;
			}

			currentBufferSize = consumedSize;
		}
	}

	flushBuffer();

	return writer ? consumedSize : utility::Reader::npos;
}

utility::Writer* ConsumerWriter::getWriter() const noexcept {
	return writer;
}

std::size_t ConsumerWriter::getCurrentBufferSize() const noexcept {
	return currentBufferSize;
}

void ConsumerWriter::flushBuffer() {
	if(writer == nullptr) {
		currentBufferSize = 0;
		return;
	}

	if(currentBufferSize > 0) {
		std::size_t producedSize = writer->write(&buffer[maxBufferSize-currentBufferSize], currentBufferSize);

		if(producedSize == utility::Writer::npos) {
			writer = nullptr;
			currentBufferSize = 0;
			return;
		}

		if(producedSize > currentBufferSize) {
			logger.warn << "esl::utility::Writer says " << producedSize << " bytes written but wrote at most " << currentBufferSize << " bytes.\n";
			producedSize = currentBufferSize;
		}

		currentBufferSize -= producedSize;
	}
}

} /* namespace process */
} /* namespace system */
} /* namespace esl */
