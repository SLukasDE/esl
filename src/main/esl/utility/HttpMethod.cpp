/*
MIT License
Copyright (c) 2019-2022 Sven Lukas

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

#include <esl/utility/HttpMethod.h>

namespace esl {
namespace utility {

template<>
const std::string& HttpMethod::toString(HttpMethodType httpMethodType) noexcept {
	static const std::string strEmpty;
	static const std::string strHttpGet = "GET";
	static const std::string strHttpPut = "PUT";
	static const std::string strHttpPost = "POST";
	static const std::string strHttpDelete = "DELETE";
	static const std::string strHttpHead = "HEAD";
	static const std::string strHttpPatch = "PATCH";
	static const std::string strHttpOptions = "OPTIONS";

	switch(httpMethodType) {
	case httpGet:
		return strHttpGet;
	case httpPut:
		return strHttpPut;
	case httpPost:
		return strHttpPost;
	case httpDelete:
		return strHttpDelete;
	case httpHead:
		return strHttpHead;
	case httpPatch:
		return strHttpPatch;
	case httpOptions:
		return strHttpOptions;
	}
	return strEmpty;
}

} /* namespace utility */
} /* namespace esl */
