#ifndef ESL_UTILITY_EBCDIC273_H_
#define ESL_UTILITY_EBCDIC273_H_

#include <string>

namespace esl {
inline namespace v1_6 {
namespace utility {

class Ebcdic273 {
public:
	static std::string toLatin1(const std::string& str);

private:
	Ebcdic273() = default;
	~Ebcdic273() = default;
};

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_EBCDIC273_H_ */
