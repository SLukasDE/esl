/*
 * This file is part of ESL.
 * Copyright (C) 2020-2023 Sven Lukas
 *
 * ESL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ESL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License
 * along with ESL.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef ESL_UTILITY_STRING_H_
#define ESL_UTILITY_STRING_H_

#include <esl/system/Stacktrace.h>

#include <functional>
#include <limits>
#include <set>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace esl {
inline namespace v1_6 {
namespace utility {

class String final {
public:
	String() = delete;

	static std::vector<std::string> split(const std::string& str, const char separator, bool dropEmptyContent = false);
	static std::vector<std::string> split(const std::string& str, const std::set<char>& separators, bool dropEmptyContent = false);

	static std::string ltrim(std::string str, char trimCharacter = ' ');
	static std::string rtrim(std::string str, char trimCharacter = ' ');
	static std::string trim(std::string str, char trimCharacter = ' ');

	static std::string toUpper(std::string str);
	static std::string toLower(std::string str);

	static bool toBool(const std::string& str);

	template<typename OType>
	static OType toNumber(const std::string& str) {
		try {
			return checkedNumericConvert<OType>(NumericTraits<OType>::convert(str));
		}
		catch(const std::invalid_argument& e) {
			if(esl::system::Stacktrace::get(e)) {
				throw;
			}
			throw esl::system::Stacktrace::add(e);
	    }
		catch(const std::out_of_range& e) {
			if(esl::system::Stacktrace::get(e)) {
				throw;
			}
			throw esl::system::Stacktrace::add(e);
	    }
	}

	/* converts a string and replaces characters that need to be replaced by an escape sequence according to the second parameter */
	static std::string toEscape(const std::string& str,
			std::function<std::string(char)> toEscapeSequenceFunction = toEscapeSequence);

	/* converts a single character to string.
	 * If character needs to be escaped then the corresponding escape sequence will be returned.
	 */
	static std::string toEscapeSequence(char character);

	/* converts a string and replaces escape sequences to the corresponding characters according to the second parameter */
	static std::string fromEscape(const std::string& str,
			std::function<char(std::string::const_iterator&, const std::string::const_iterator&)> fromEscapeSequenceFunction = fromEscapeSequence);

	/* This function returns the character pointed by the first parameter and moves first parameter to next character.
	 * If first parameter is pointing to an escape sequence it returns the translated result.
	 */
	static char fromEscapeSequence(std::string::const_iterator& escapeSequenceIterator, const std::string::const_iterator& escapeSequenceEnd);

	enum Base64Variant {
		base64, base64url
	};
	static std::string toBase16(const std::string& str);
	static std::string toBase64(const std::string& str, Base64Variant base64Variant = base64url, bool withPadding = false);
	static std::string fromBase64(const std::string& base64str, bool acceptFormatting = false);

	static std::string toURLEncoded(const std::string& str);
	static std::string fromURLEncoded(const std::string& urlEncodedStr);

private:
	template<typename OType, bool Dummy = true>
	struct NumericTraits;

	/* Caution: This method returns an int, because there exists no std::stoc(...) */
	template<bool Dummy>
	struct NumericTraits<signed char, Dummy> {
		static int convert(const std::string& str) {
			return std::stoi(str);
		}
	};

	/* Caution: This method returns an unsigned long, because there exists no std::stouc(...) */
	template<bool Dummy>
	struct NumericTraits<unsigned char, Dummy> {
		static unsigned long convert(const std::string& str) {
			return std::stoul(str);
		}
	};

	/* Caution: This method returns an int, because there exists no std::stos(...) */
	template<bool Dummy>
	struct NumericTraits<short, Dummy> {
		static int convert(const std::string& str) {
			return std::stoi(str);
		}
	};

	/* Caution: This method returns an unsigned long, because there exists no std::stous(...) */
	template<bool Dummy>
	struct NumericTraits<unsigned short, Dummy> {
		static unsigned long convert(const std::string& str) {
			return std::stoul(str);
		}
	};

	template<bool Dummy>
	struct NumericTraits<int, Dummy> {
		static int convert(const std::string& str) {
			return std::stoi(str);
		}
	};

	/* Caution: This method returns an unsigned long, because there exists no std::stoui(...) */
	template<bool Dummy>
	struct NumericTraits<unsigned int, Dummy> {
		static unsigned long convert(const std::string& str) {
			return std::stoul(str);
		}
	};

	template<bool Dummy>
	struct NumericTraits<long, Dummy> {
		static long convert(const std::string& str) {
			return std::stol(str);
		}
	};

	template<bool Dummy>
	struct NumericTraits<unsigned long, Dummy> {
		static unsigned long convert(const std::string& str) {
			return std::stoul(str);
		}
	};

	template<bool Dummy>
	struct NumericTraits<long long, Dummy> {
		static long long convert(const std::string& str) {
			return std::stoll(str);
		}
	};

	template<bool Dummy>
	struct NumericTraits<unsigned long long, Dummy> {
		static unsigned long long convert(const std::string& str) {
			return std::stoull(str);
		}
	};

	template<bool Dummy>
	struct NumericTraits<float, Dummy> {
		static float convert(const std::string& str) {
			return std::stof(str);
		}
	};

	template<bool Dummy>
	struct NumericTraits<double, Dummy> {
		static double convert(const std::string& str) {
			return std::stod(str);
		}
	};

	template<bool Dummy>
	struct NumericTraits<long double, Dummy> {
		static long double convert(const std::string& str) {
			return std::stold(str);
		}
	};

	template<typename OType, typename IType>
	static OType checkedNumericConvert(IType inputValue) {
	    if(std::is_signed<IType>::value && std::is_unsigned<OType>::value && inputValue < 0) {
	        throw esl::system::Stacktrace::add(std::runtime_error("Converting negative number to unsigned integer type"));
	    }
	    if(std::is_signed<IType>::value && std::is_signed<OType>::value && inputValue < std::numeric_limits<OType>::lowest()) {
	        throw esl::system::Stacktrace::add(std::runtime_error("Numeric underflow in conversion"));
	    }
	    if(inputValue > std::numeric_limits<OType>::max()) {
	        throw esl::system::Stacktrace::add(std::runtime_error("Numeric overflow in conversion"));
	    }
	    return static_cast<OType>(inputValue);
	}
};

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_STRING_H_ */
