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

#include <esl/io/input/String.h>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace input {

std::size_t String::write(const void* data, std::size_t size) {
	if(done) {
		return npos;
	}

	if(size > 0) {
		str += std::string(static_cast<const char*>(data), size);
		return size;
	}

	done = true;
	process();
	return npos;
}

std::size_t String::getSizeWritable() const {
	return npos;
}

void String::process() {
}

const std::string& String::getString() const noexcept {
	return str;
}

} /* namespace input */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */
