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

#ifndef ESL_IO_INPUT_STRING_H_
#define ESL_IO_INPUT_STRING_H_

#include <esl/io/Writer.h>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace input {

class String : Writer {
public:
	// if function is called with size=0, this signals that writing is done, so write will not be called anymore.
	// -> this can be used for cleanup stuff.
	// returns consumed bytes.
	// npos is returned if writer will not consume anymore.
	std::size_t write(const void* data, std::size_t size) override;

	// returns consumable bytes to write.
	// npos is returned if available size is unknown.
	std::size_t getSizeWritable() const override;

	virtual void process();

	const std::string& getString() const noexcept;

private:
	bool done = false;
	std::string str;
};

} /* namespace input */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_IO_INPUT_STRING_H_ */
