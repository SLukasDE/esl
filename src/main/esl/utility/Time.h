/*
MIT License
Copyright (c) 2019, 2020 Sven Lukas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef ESL_UTILITY_TIME_H_
#define ESL_UTILITY_TIME_H_

#include <string>
#include <ctime>
#include <locale>
#include <chrono>

namespace esl {
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
		struct tm tm;
		const char* ptr = strptime(str.c_str(), format, &tm);
		if(ptr == nullptr || *ptr != '\0') {
			return std::chrono::time_point<std::chrono::system_clock>::min();
		}
		return T::from_time_t(mktime(&tm));
	}

private:
};

} /* namespace utility */
} /* namespace esl */

#endif /* ESL_UTILITY_TIME_H_ */
