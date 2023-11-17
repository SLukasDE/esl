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

#ifndef ESL_IO_OUTPUT_MEMORY_H_
#define ESL_IO_OUTPUT_MEMORY_H_

#include <esl/io/Output.h>
#include <esl/io/Producer.h>
#include <esl/io/Writer.h>

#include <string>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace output {

class Memory : public Producer {
public:
	static Output create(const void* data, std::size_t size);

	Memory(const void* data, std::size_t size);

	std::size_t produce(esl::io::Writer& writer) override;

	const void* getData() const noexcept;
	std::size_t getSize() const noexcept;

private:
	const void* data;
	std::size_t size;
	std::size_t currentPos = 0;
};

} /* namespace output */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_IO_OUTPUT_MEMORY_H_ */
