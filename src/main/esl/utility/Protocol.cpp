/*
MIT License
Copyright (c) 2019-2025 Sven Lukas

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
