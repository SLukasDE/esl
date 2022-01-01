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

#include <esl/io/output/Buffered.h>
#include <esl/logging/Logger.h>

#include <cstring>
#include <algorithm>

namespace esl {
namespace io {
namespace output {

namespace {
logging::Logger<> logger("esl::io::output::Buffered");
}

constexpr std::size_t Buffered::prefetchSize;

esl::io::Output Buffered::create(Reader& baseReader) {
	return esl::io::Output(std::unique_ptr<Reader>(new Buffered(baseReader)));
}

Buffered::Buffered(Reader& aBaseReader)
: baseReader(std::ref(aBaseReader))
{ }

std::size_t Buffered::read(void* data, std::size_t size) {
	/* check if there are still some bytes available in current cache line */
	if(currentIndex != npos && buffers[currentIndex]->size() > currentPos) {
		CacheLine& cacheLine = *buffers[currentIndex];

		if(size > 0) {
			size = std::min(size, cacheLine.size() - currentPos);
			std::memcpy(data, &cacheLine[currentPos], size);
		}

		currentPos += size;

		if(cacheLine.size() <= currentPos) {
			if(buffers.size() > currentIndex+1) {
				currentPos = 0;
				++currentIndex;
			}
		}
	}
	/* check if there are no more bytes available in whole buffer */
	//if(currentIndex == npos || buffers[currentIndex]->size() <= currentPos) {
	else {
		if(completed) {
			return npos;
		}

		std::size_t capacity = baseReader.get().getSizeReadable();
		if(capacity == 0) {
			if(baseReader.get().read(nullptr, 0) == npos) {
				completed = true;
			}
			return 0;
		}

		if(capacity == npos) {
			capacity = prefetchSize;
		}
		if(capacity > size) {
			capacity = size;
		}

		buffers.push_back(std::unique_ptr<std::vector<std::uint8_t>>(new std::vector<std::uint8_t>(capacity)));
		CacheLine& cacheLine = *buffers.back();

		size = baseReader.get().read(&cacheLine[0], capacity);

		if(size == 0) {
			buffers.pop_back();
		}
		else if(size == npos) {
			buffers.pop_back();
			completed = true;
		}
		else {
			if(capacity > size) {
				cacheLine.resize(size);
			}

			currentIndex = buffers.size() - 1;
			currentPos = size;

			std::memcpy(data, &cacheLine[0], size);
		}
	}

	return size;
}

std::size_t Buffered::getSizeReadable() const {
	/* check if there are still some bytes available in current cache line */
	if(currentIndex != npos && buffers[currentIndex]->size() > currentPos) {
		CacheLine& cacheLine = *buffers[currentIndex];

		return cacheLine.size() - currentPos;
	}
	/* check if there are no more bytes available in whole buffer */
	//if(currentIndex == npos || buffers[currentIndex]->size() <= currentPos) {
	else {
		if(completed) {
			return 0;
		}
		return baseReader.get().getSizeReadable();
	}
}

bool Buffered::hasSize() const {
	return !completed;
}

std::size_t Buffered::getSize() const {
	std::size_t rv = Reader::npos;
	if(completed) {
		rv = 0;
		for(const auto& cacheLinePtr : buffers) {
			if(cacheLinePtr) {
				rv += cacheLinePtr->size();
			}
		}
	}
	return rv;
}

void Buffered::setBaseReader(Reader& aBaseReader) {
	baseReader = std::ref(aBaseReader);
}

void Buffered::reset() {
	currentIndex = buffers.empty() ? npos : 0;
	currentPos = 0;
}

} /* namespace output */
} /* namespace io */
} /* namespace esl */
