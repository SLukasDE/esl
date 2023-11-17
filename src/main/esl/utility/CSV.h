#ifndef ESL_UTILITY_CSV_H_
#define ESL_UTILITY_CSV_H_

#include <string>
#include <vector>

namespace esl {
inline namespace v1_6 {
namespace utility {

class CSV {
public:
	CSV(char separator = ',');

	std::vector<std::string> splitRow(const std::string& line);
	std::string toRow(const std::vector<std::string>& columns);

private:
	char separator;
};

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_CSV_H_ */
