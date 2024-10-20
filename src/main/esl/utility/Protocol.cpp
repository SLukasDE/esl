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

#include <esl/utility/Protocol.h>

namespace esa {
inline namespace v1_6 {
namespace utility {

template<>
const std::string& Enum<esl::utility::ProtocolType, esl::utility::ProtocolType::file>::toString(esl::utility::ProtocolType protocolType) noexcept {
	static const std::string strEmpty;
	static const std::string strFile = "file";
	static const std::string strHttp = "http";
	static const std::string strHttps = "https";

	switch(protocolType) {
	case esl::utility::ProtocolType::file:
		return strFile;
	case esl::utility::ProtocolType::http:
		return strHttp;
	case esl::utility::ProtocolType::https:
		return strHttps;
	default:
		break;
	}
	return strEmpty;
}

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esa */
