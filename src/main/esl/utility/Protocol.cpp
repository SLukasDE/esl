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

#include <esl/utility/Protocol.h>

#include <algorithm>

namespace esl {
namespace utility {

namespace {
const std::string strEmpty;
const std::string strProtocolHttp = "http";
const std::string strProtocolHttps = "https";
}

Protocol::Protocol(Type type) noexcept
: hasEnum(true),
  enumType(type)
{ }

Protocol::Protocol(std::string type) noexcept
: hasEnum(false),
  stringType(std::move(type))
{ }

bool Protocol::operator==(Protocol::Type type) const noexcept {
	return (*this == Protocol(type));
}

bool Protocol::operator==(const Protocol& aMime) const noexcept {
	if(hasEnum && aMime.hasEnum) {
		return enumType == aMime.enumType;
	}
	return toString() == aMime.toString();
}

bool Protocol::operator!=(Protocol::Type type) const noexcept {
	return (*this != Protocol(type));
}

bool Protocol::operator!=(const Protocol& aMime) const noexcept {
	if(hasEnum && aMime.hasEnum) {
		return enumType != aMime.enumType;
	}
	return toString() != aMime.toString();
}

const std::string& Protocol::toString() const noexcept {
	if(hasEnum) {
		return toString(enumType);
	}

	return stringType;
}

const std::string& Protocol::toString(Protocol::Type mimeType) noexcept {
	switch(mimeType) {
	case protocolHttp:
		return strProtocolHttp;
	case protocolHttps:
		return strProtocolHttps;
	case protocolNone:
		break;
	}
	return strEmpty;
}

} /* namespace utility */
} /* namespace esl */
