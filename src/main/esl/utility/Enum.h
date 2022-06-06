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

#ifndef ESL_UTILITY_ENUM_H_
#define ESL_UTILITY_ENUM_H_

#include <memory>
#include <stdexcept>
#include <string>

namespace esl {
namespace utility {

template<typename EnumType, EnumType defaultType>
class Enum {
public:
	using Type = EnumType;

	Enum() = default;

	Enum(EnumType type) noexcept
	: hasEnum(true),
	  enumType(type)
	{ }

	explicit Enum(std::string type) noexcept
	: hasEnum(false),
	  stringType(std::move(type))
	{ }

	explicit operator bool() const noexcept {
		return hasEnum || !stringType.empty();
	}

	bool operator==(EnumType type) const noexcept {
		return (*this == Enum(type));
	}

	bool operator==(const Enum& aEnum) const noexcept {
		if(hasEnum && aEnum.hasEnum) {
			return enumType == aEnum.enumType;
		}
		return toString() == aEnum.toString();
	}

	bool operator!=(EnumType type) const noexcept {
		return (*this != Enum(type));
	}

	bool operator!=(const Enum& aEnum) const noexcept {
		if(hasEnum && aEnum.hasEnum) {
			return enumType != aEnum.enumType;
		}
		return toString() != aEnum.toString();
	}

	bool isEnumType() const noexcept {
		return hasEnum;
	}

	EnumType getEnumType() const {
		if(!hasEnum) {
			throw std::runtime_error("cannot get enum type because it's a string");
		}
		return enumType;
	}

	const std::string& toString() const noexcept {
		if(hasEnum) {
			return toString(enumType);
		}

		return stringType;
	}

	static const std::string& toString(EnumType mimeType) noexcept;

private:
	bool hasEnum = false;
	EnumType enumType = defaultType;
	std::string stringType;
};

} /* namespace utility */
} /* namespace esl */

#endif /* ESL_UTILITY_ENUM_H_ */
