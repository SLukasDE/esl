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

#include <esl/module/InterfaceType.h>

#include <algorithm>


namespace esl {
namespace module {

namespace {
const std::string strEmpty;
const std::string strEslComBasicClient = "esl-com-basic-client";
const std::string strEslComBasicServer = "esl-com-basic-server";
const std::string strEslComBasicServerRequestHandler = "esl-com-basic-server-requesthandler";
const std::string strEslComHttpClient = "esl-com-http-client";
const std::string strEslComHttpServer = "esl-com-http-server";
const std::string strEslComHttpServerRequestHandler = "esl-com-http-server-requesthandler";
const std::string strEslDatabase = "esl-database";
const std::string strEslObject = "esl-object";
}

InterfaceType::InterfaceType(Type type) noexcept
: hasEnum(true),
  enumType(type)
{ }

InterfaceType::InterfaceType(std::string type) noexcept
: hasEnum(false),
  stringType(std::move(type))
{ }

InterfaceType::operator bool() const noexcept {
	return hasEnum || !stringType.empty();
}

bool InterfaceType::operator==(InterfaceType::Type type) const noexcept {
	return (*this == InterfaceType(type));
}

bool InterfaceType::operator==(const InterfaceType& aProtocol) const noexcept {
	if(hasEnum && aProtocol.hasEnum) {
		return enumType == aProtocol.enumType;
	}
	return toString() == aProtocol.toString();
}

bool InterfaceType::operator!=(InterfaceType::Type type) const noexcept {
	return (*this != InterfaceType(type));
}

bool InterfaceType::operator!=(const InterfaceType& aProtocol) const noexcept {
	if(hasEnum && aProtocol.hasEnum) {
		return enumType != aProtocol.enumType;
	}
	return toString() != aProtocol.toString();
}

const std::string& InterfaceType::toString() const noexcept {
	if(hasEnum) {
		return toString(enumType);
	}

	return stringType;
}

const std::string& InterfaceType::toString(InterfaceType::Type type) noexcept {
	switch(type) {
	case esl__com__basic__client:
		return strEslComBasicClient;
	case esl__com__basic__server:
		return strEslComBasicServer;
	case esl__com__basic__server__requesthandler:
		return strEslComBasicServerRequestHandler;

	case esl__com__http__client:
		return strEslComHttpClient;
	case esl__com__http__server:
		return strEslComHttpServer;
	case esl__com__http__server__requesthandler:
		return strEslComHttpServerRequestHandler;
	default:
		break;

	case esl__database:
		return strEslDatabase;

	case esl__object:
		return strEslObject;
	}

	return strEmpty;
}

} /* namespace module */
} /* namespace esl */
