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

#ifndef ESL_IO_OUTPUT_FUNCTION_H_
#define ESL_IO_OUTPUT_FUNCTION_H_

#include <esl/io/Output.h>
#include <esl/io/Reader.h>

#include <functional>
#include <string>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace output {

class Function : public Reader {
public:
	static Output create(std::function<std::size_t(void*, std::size_t)> getDataFunction);

	Function(std::function<std::size_t(void*, std::size_t)> getDataFunction);

	std::size_t read(void* data, std::size_t size) override;
	std::size_t getSizeReadable() const override;
	bool hasSize() const override;
	std::size_t getSize() const override;

private:
	static constexpr std::size_t prefetchSize = 1024;
	std::size_t prefetchData() const;

	mutable std::function<std::size_t(void*, std::size_t)> getDataFunction;
	mutable std::size_t fetchedDirectSize = 0;

	mutable std::string data;
	std::size_t dataPos = 0;
};

} /* namespace output */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_IO_OUTPUT_FUNCTION_H_ */
