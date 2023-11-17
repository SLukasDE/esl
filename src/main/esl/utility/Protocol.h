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
