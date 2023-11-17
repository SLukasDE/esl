/*
 * This file is part of ESL.
 * Copyright (C) 2020-2023 Sven Lukas
 *
 * ESL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ESL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License
 * along with ESL.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <esl/io/output/Buffered.h>
#include <esl/Logger.h>

#include <algorithm>
#include <cstring>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace output {

namespace {
Logger logger("esl::io::output::Buffered");
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
} /* inline namespace v1_6 */
} /* namespace esl */
