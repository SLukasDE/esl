#ifndef ESL_UTILITY_TIME_H_
#define ESL_UTILITY_TIME_H_

#include <string>
#include <ctime>
#include <locale>
#include <chrono>

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
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_TIME_H_ */
