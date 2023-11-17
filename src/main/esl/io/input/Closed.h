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

#ifndef ESL_IO_INPUT_CLOSED_H_
#define ESL_IO_INPUT_CLOSED_H_

#include <esl/io/Writer.h>
#include <esl/io/Input.h>

#include <memory>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace input {

class Closed : public Writer {
public:
	static Input create();

	std::size_t write(const void* data, std::size_t size) override;
	std::size_t getSizeWritable() const override;
};

} /* namespace input */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_IO_INPUT_CLOSED_H_ */
