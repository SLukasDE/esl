#include <esl/utility/Protocol.h>

namespace esl {
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
} /* namespace esl */
