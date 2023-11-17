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

#include <esl/io/input/Closed.h>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace input {

namespace {
Closed closed;
}

esl::io::Input Closed::create() {
	return esl::io::Input(closed);
}

std::size_t Closed::write(const void* data, std::size_t size) {
	return npos;
}

std::size_t Closed::getSizeWritable() const {
	return 0;
}

} /* namespace input */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */
