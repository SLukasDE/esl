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

#include <esl/io/output/Memory.h>
#include <esl/logging/Logger.h>

namespace esl {
namespace io {
namespace output {

namespace {
esl::logging::Logger<> logger("esl::com::basic::client::Connection");
}

esl::io::Output Memory::create(const void* data, std::size_t size) {
    return esl::io::Output(std::unique_ptr<esl::io::Producer>(new Memory(data, size)));
}

Memory::Memory(const void* aData, std::size_t aSize)
: data(aData),
  size(aSize)
{ }

std::size_t Memory::produce(Writer& writer) {
	if(currentPos >= size) {
		size = Writer::npos;
	}

	if(size == Writer::npos) {
		return Writer::npos;
	}

	std::size_t count = writer.write(&static_cast<const char*>(getData())[currentPos], size - currentPos);
	//std::size_t count = writer.write(static_cast<const char*>(getData()) + currentPos, size - currentPos);
	if(count == Writer::npos) {
		currentPos = size;
	}
	else {
		if(count > size - currentPos) {
			logger.warn << "output::Memory has been called with a broken writer!\n";
			logger.warn << "Writer read " << count << " bytes but at most " << (size - currentPos) << " bytes was allowed to read.\n";
			count = size - currentPos;
		}
		currentPos += count;
	}

	return count;
}

const void* Memory::getData() const noexcept {
	return data;
}

std::size_t Memory::getSize() const noexcept {
	return size;
}

} /* namespace output */
} /* namespace io */
} /* namespace esl */
