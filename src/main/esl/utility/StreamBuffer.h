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

#ifndef ESL_UTILITY_STREAMBUFFER_H_
#define ESL_UTILITY_STREAMBUFFER_H_

#include <functional>
#include <streambuf>
#include <vector>

namespace esl {
inline namespace v1_6 {
namespace utility {

class StreamBuffer : public std::streambuf {
public:
    StreamBuffer(std::size_t bufferSize, std::function<void(const char*, std::size_t)> writeHandler);

private:
    int_type overflow(int_type ch) override;
    int sync() override;

    std::size_t bufferSize;
    std::vector<char> buffer;
    std::function<void(const char*, std::size_t)> writeHandler;
};

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_STREAMBUFFER_H_ */
