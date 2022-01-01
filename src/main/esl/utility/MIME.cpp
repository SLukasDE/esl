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

#include <esl/utility/MIME.h>

#include <algorithm>

namespace esl {
namespace utility {

namespace {

const std::string strEmpty;
const std::string strTextPlain = "text/plain";
const std::string strTextHtml = "text/html";
const std::string strTextXml = "text/xml";
const std::string strTextCsv = "text/comma-separated-values";
const std::string strApplicationXml = "application/xml";
const std::string strApplicationJson = "application/json";

}

MIME::MIME(Type type) noexcept
: hasEnum(true),
  enumType(type)
{ }

MIME::MIME(std::string type) noexcept
: hasEnum(false),
  stringType(std::move(type))
{ }

MIME::operator bool() const noexcept {
	return hasEnum || !stringType.empty();
}

bool MIME::operator==(MIME::Type type) const noexcept {
	return (*this == MIME(type));
}

bool MIME::operator==(const MIME& aMime) const noexcept {
	if(hasEnum && aMime.hasEnum) {
		return enumType == aMime.enumType;
	}
	return toString() == aMime.toString();
}

bool MIME::operator!=(MIME::Type type) const noexcept {
	return (*this != MIME(type));
}

bool MIME::operator!=(const MIME& aMime) const noexcept {
	if(hasEnum && aMime.hasEnum) {
		return enumType != aMime.enumType;
	}
	return toString() != aMime.toString();
}

const std::string& MIME::toString() const noexcept {
	if(hasEnum) {
		return toString(enumType);
	}

	return stringType;
}

const std::string& MIME::toString(MIME::Type mimeType) noexcept {
	switch(mimeType) {
	//case empty:
	//	return strEmpty;
	case textPlain:
		return strTextPlain;
	case textHtml:
		return strTextHtml;
	case textXml:
		return strTextXml;
	case textCsv:
		return strTextCsv;
	case applicationXml:
		return strApplicationXml;
	case applicationJson:
		return strApplicationJson;
	}
	return strEmpty;
}

} /* namespace utility */
} /* namespace esl */

