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

#ifndef ESL_IO_OUTPUT_BUFFERED_H_
#define ESL_IO_OUTPUT_BUFFERED_H_

#include <esl/io/Output.h>
#include <esl/io/Reader.h>

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace output {

class Buffered : public Reader {
public:
	static Output create(Reader& baseReader);

	Buffered(Reader& baseReader);

	std::size_t read(void* data, std::size_t size) override;
	std::size_t getSizeReadable() const override;
	bool hasSize() const override;
	std::size_t getSize() const override;

	void setBaseReader(Reader& baseReader);

	void reset();

private:
	static constexpr std::size_t prefetchSize = 4096;

	using CacheLine = std::vector<std::uint8_t>;

	std::reference_wrapper<Reader> baseReader;

	bool completed = false;
	std::size_t currentIndex = npos;
	std::size_t currentPos = 0;

	std::vector<std::unique_ptr<CacheLine>> buffers;
};

} /* namespace output */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_IO_OUTPUT_BUFFERED_H_ */
