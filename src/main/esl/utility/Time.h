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

#ifndef ESL_UTILITY_TIME_H_
#define ESL_UTILITY_TIME_H_

#include <string>
#include <ctime>
#include <locale>
#include <chrono>

#ifdef _WIN32
#include <time.h>
#include <iomanip>
#include <sstream>
#endif

namespace esl {
inline namespace v1_6 {
namespace utility {

class Time {
public:
	Time() = default;
	~Time() = default;

	template<typename T>
	static std::string toString(const typename T::time_point& timePoint, const char* format = "%Y-%m-%d %H:%M:%S") {
		std::time_t t = T::to_time_t(timePoint);
		struct tm tm = *std::localtime(&t);
		char buf[255];
	//	memset(&tm, 0, sizeof(struct tm));
		strftime(buf, sizeof(buf), format, &tm);
		return buf;
	}

	template<typename T>
	static typename T::time_point fromString(const std::string& str, const char* format = "%Y-%m-%d %H:%M:%S") {
		struct tm timeStruct;
#ifdef _WIN32
		std::istringstream input(str.c_str());
		input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
		input >> std::get_time(&timeStruct, format);
		if (input.fail()) {
			return std::chrono::time_point<std::chrono::system_clock>::min();
		}
#else
		const char* ptr = strptime(str.c_str(), format, &timeStruct);
		if(ptr == nullptr || *ptr != '\0') {
			return std::chrono::time_point<std::chrono::system_clock>::min();
		}
#endif
		return T::from_time_t(mktime(&timeStruct));
	}

private:
};

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_TIME_H_ */
