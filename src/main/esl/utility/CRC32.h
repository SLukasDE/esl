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

#ifndef ESL_UTILITY_CRC32_H_
#define ESL_UTILITY_CRC32_H_

#include <cstdint>
#include <string>

namespace esl {
inline namespace v1_6 {
namespace utility {

class CRC32 {
public:
	CRC32(std::uint32_t initialValue = 0);

	CRC32& pushData(const void* data, std::size_t length);
	std::uint32_t get() const noexcept;

	static inline std::uint32_t calculate(const void* data, std::size_t length, std::uint32_t crc32 = 0) {
		return CRC32(crc32).pushData(data, length).get();
	}

private:
	std::uint32_t value;
};

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_CRC32_H_ */
