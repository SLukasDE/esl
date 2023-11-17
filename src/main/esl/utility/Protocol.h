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

#ifndef ESL_UTILITY_PROTOCOL_H_
#define ESL_UTILITY_PROTOCOL_H_

#include <esl/utility/Enum.h>

#include <string>

namespace esl {
inline namespace v1_6 {
namespace utility {

enum ProtocolType {
	file,
	http,
	https
};

using Protocol = esa::utility::Enum<ProtocolType, ProtocolType::file>;

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

namespace esa {
inline namespace v1_6 {
namespace utility {

template<>
const std::string& Enum<esl::utility::ProtocolType, esl::utility::ProtocolType::file>::toString(esl::utility::ProtocolType protocolType) noexcept;

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esa */

#endif /* ESL_UTILITY_PROTOCOL_H_ */
