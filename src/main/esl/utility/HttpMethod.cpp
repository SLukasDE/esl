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

#include <esl/utility/HttpMethod.h>

#include <algorithm>

namespace esl {
namespace utility {

namespace {
const std::string strEmpty;
const std::string strHttpGet = "GET";
const std::string strHttpPut = "PUT";
const std::string strHttpPost = "POST";
const std::string strHttpDelete = "DELETE";
const std::string strHttpHead = "HEAD";
const std::string strHttpPatch = "PATCH";
const std::string strHttpOptions = "OPTIONS";
}

HttpMethod::HttpMethod(Type type) noexcept
: hasEnum(true),
  enumType(type)
{ }

HttpMethod::HttpMethod(std::string type) noexcept
: hasEnum(false),
  stringType(std::move(type))
{ }

bool HttpMethod::operator==(HttpMethod::Type type) const noexcept {
	return (*this == HttpMethod(type));
}

bool HttpMethod::operator==(const HttpMethod& aMime) const noexcept {
	if(hasEnum && aMime.hasEnum) {
		return enumType == aMime.enumType;
	}
	return toString() == aMime.toString();
}

bool HttpMethod::operator!=(HttpMethod::Type type) const noexcept {
	return (*this != HttpMethod(type));
}

bool HttpMethod::operator!=(const HttpMethod& aMime) const noexcept {
	return (*this != aMime);
}

const std::string& HttpMethod::toString() const noexcept {
	if(hasEnum) {
		return toString(enumType);
	}

	return stringType;
}

const std::string& HttpMethod::toString(HttpMethod::Type mimeType) noexcept {
	switch(mimeType) {
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
