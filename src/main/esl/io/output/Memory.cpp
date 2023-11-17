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

#include <esl/io/output/Memory.h>
#include <esl/Logger.h>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace output {

namespace {
Logger logger("esl::io::output::Memory");
}

esl::io::Output Memory::create(const void* data, std::size_t size) {
    return esl::io::Output(std::unique_ptr<esl::io::Producer>(new Memory(data, size)));
}

Memory::Memory(const void* aData, std::size_t aSize)
: data(aData),
  size(aSize)
{ }

std::size_t Memory::produce(esl::io::Writer& writer) {
	if(currentPos >= size) {
		size = esl::io::Writer::npos;
	}

	if(size == esl::io::Writer::npos) {
		return esl::io::Writer::npos;
	}

	std::size_t count = writer.write(&static_cast<const char*>(getData())[currentPos], size - currentPos);
	//std::size_t count = writer.write(static_cast<const char*>(getData()) + currentPos, size - currentPos);
	if(count == esl::io::Writer::npos) {
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
} /* inline namespace v1_6 */
} /* namespace esl */
