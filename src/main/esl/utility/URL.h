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

#ifndef ESL_UTILITY_URL_H_
#define ESL_UTILITY_URL_H_

#include <esl/utility/Protocol.h>

#include <string>

namespace esl {
inline namespace v1_6 {
namespace utility {

class URL {
public:
	URL(std::string url);

	const std::string& toString() const noexcept;
	const Protocol& getScheme() const noexcept;
	const std::string& getHostname() const noexcept;
	const std::string& getPort() const noexcept;
	const std::string& getPath() const noexcept;
	const std::string& getQuery() const noexcept;
	const std::string& getTag() const noexcept;

private:
	enum class NextFragment {
		SCHEME,
		HOSTNAME,
		PORT,
		PATH,
		QUERY,
		TAG,
		EMPTY
	};
	NextFragment parseScheme(size_t& pos, const char* str, const size_t len);
	NextFragment parseHostname(size_t& pos, const char* str, const size_t len);
	NextFragment parsePort(size_t& pos, const char* str, const size_t len);
	NextFragment parsePath(size_t& pos, const char* str, const size_t len);
	NextFragment parseQuery(size_t& pos, const char* str, const size_t len);
	NextFragment parseTag(size_t& pos, const char* str, const size_t len);

	std::string url;

	Protocol scheme;
	std::string hostname;
	std::string port;
	std::string path;
	std::string query;
	std::string tag;
};

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_URL_H_ */
