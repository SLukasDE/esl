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

#include <esl/utility/String.h>

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iterator>
#include <map>
#include <utility>

namespace esl {
inline namespace v1_6 {
namespace utility {

namespace {
std::map<char, std::string> asciiToEscapeSequences = {
		std::make_pair('\\', "\\\\"),
		std::make_pair('\a', "\\a"),
		std::make_pair('\b', "\\b"),
		std::make_pair('\f', "\\f"),
		std::make_pair('\n', "\\n"),
		std::make_pair('\r', "\\r"),
		std::make_pair('\t', "\\t"),
		std::make_pair('\v', "\\v"),
		std::make_pair('\0', "\\0")
};

std::map<std::string, char> asciiFromEscapeSequences = {
		std::make_pair("\\\\", '\\'),
		std::make_pair("\\\a", '\a'),
		std::make_pair("\\\b", '\b'),
		std::make_pair("\\\f", '\f'),
		std::make_pair("\\\n", '\n'),
		std::make_pair("\\\r", '\r'),
		std::make_pair("\\\t", '\t'),
		std::make_pair("\\\v", '\v'),
		std::make_pair("\\\0", '\0')
};

std::string base64Chars("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
std::string base64urlChars("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_");

std::string decodeBase64Buffer(std::size_t bufferIndex, unsigned char* buffer) {
	std::string str;

	for(std::size_t index = bufferIndex; index<4; ++index) {
		buffer[index] = 0;
	}

	for(std::size_t index = 0; index<4; ++index) {
		std::size_t pos = base64Chars.find(buffer[index]);
		if(pos == std::string::npos) {
			pos = base64urlChars.find(buffer[index]);
		}
		buffer[index] = pos;
	}

	unsigned char tmpBuffer[3];
	tmpBuffer[0] = (buffer[0] << 2) + ((buffer[1] & 0x30) >> 4);
	tmpBuffer[1] = ((buffer[1] & 0xf) << 4) + ((buffer[2] & 0x3c) >> 2);
	tmpBuffer[2] = ((buffer[2] & 0x3) << 6) + buffer[3];

	for(std::size_t index = 0; index<bufferIndex-1; ++index) {
		str += tmpBuffer[index];
	}

	return str;
}
}

std::vector<std::string> String::split(const std::string& str, const char separator, bool dropEmptyContent) {
    return split(str, {{separator}}, dropEmptyContent);
}

std::vector<std::string> String::split(const std::string& str, const std::set<char>& separators, bool dropEmptyContent) {
    std::vector<std::string> rv;
    std::string::const_iterator currentIt = str.begin();
    std::string::const_iterator lastIt = currentIt;

    for(;currentIt != str.end(); ++currentIt) {
        if(separators.count(*currentIt) > 0) {
        	std::string content(lastIt, currentIt);
        	if(dropEmptyContent == false || content.empty() == false) {
                rv.push_back(content);
        	}

            lastIt = currentIt;
            ++lastIt;
        }
    }

    std::string content(lastIt, currentIt);
	if(dropEmptyContent == false || content.empty() == false) {
        rv.push_back(content);
	}

    return rv;
}

std::string String::ltrim(std::string str, char trimCharacter) {
    str.erase(std::begin(str), std::find_if(std::begin(str), std::end(str), [trimCharacter](int c) {
        return c != trimCharacter;
    }));

    return str;
}

std::string String::rtrim(std::string str, char trimCharacter) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [trimCharacter](int c) {
        return c != trimCharacter;
    }).base(), std::end(str));

    return str;
}

std::string String::trim(std::string str, char trimCharacter) {
    return rtrim(ltrim(str, trimCharacter), trimCharacter);
}

std::string String::toUpper(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
		return std::toupper(c);
	});
	return str;
}

std::string String::toLower(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
		return std::tolower(c);
	});
	return str;
}

bool String::toBool(const std::string& str) {
	const std::string normalized = toUpper(trim(str));

	if(normalized.empty() || normalized == "0" || normalized == "NO" || normalized == "FALSE") {
		return false;
	}

	if(normalized == "1" || normalized == "-1" || normalized == "YES" || normalized == "TRUE") {
		return true;
	}

	throw esl::system::Stacktrace::add(std::invalid_argument("Cannot convert '" + str + "' to boolean value"));
}

std::string String::toEscape(const std::string& str, std::function<std::string(char)> toEscapeSequenceFunction) {
	std::string result;

	for(char c : str) {
		result += toEscapeSequenceFunction(c);
	}

	return result;
}

std::string String::toEscapeSequence(char character) {
	auto iter = asciiToEscapeSequences.find(character);

	if(iter != std::end(asciiToEscapeSequences)) {
		return iter->second;
	}

	return std::string(1, character);
}

std::string String::fromEscape(const std::string& str, std::function<char(std::string::const_iterator&, const std::string::const_iterator&)> fromEscapeSequenceFunction) {
	std::string result;

	std::string::const_iterator iter = std::begin(str);
	std::string::const_iterator end = std::end(str);

	while(iter != end) {
		result += fromEscapeSequenceFunction(iter, std::end(str));
	}

	return result;
}

char String::fromEscapeSequence(std::string::const_iterator& escapeSequenceIterator, const std::string::const_iterator& escapeSequenceEnd) {
	auto iter = asciiFromEscapeSequences.find(std::string(escapeSequenceIterator, escapeSequenceEnd));

	if(iter != std::end(asciiFromEscapeSequences)) {
		escapeSequenceIterator += iter->first.size();
		return iter->second;
	}

	char c = *escapeSequenceIterator;
	++escapeSequenceIterator;
	return c;
}

std::string String::toBase64(const std::string& str, Base64Variant base64Variant, bool withPadding) {
	std::string result;

	for(std::size_t i = 0; i < str.size(); i += 3) {
		int packed64 = (str[i] & 0xff) << 16;
		std::size_t num64Chars = 2;

		if(i + 1 < str.size()) {
			packed64 = packed64 + ((str[i+1] & 0xff) << 8);
			num64Chars = 3;
		}

		if(i + 2 < str.size()) {
			packed64 = packed64 + (str[i+2] & 0xff);
			num64Chars = 4;
		}

		for(std::size_t j = 0; j < 4; ++j) {
			if(j < num64Chars) {
				if(base64Variant == base64url) {
					result += base64urlChars[(packed64 >> (6 * (3 - j))) & 0x3f];
				}
				else {
					result += base64Chars[(packed64 >> (6 * (3 - j))) & 0x3f];
				}
			}
			else if(withPadding) {
				if(base64Variant == base64url) {
					result += "%3d";
				}
				else {
					result += "=";
				}
			}
		}
	}
	return result;
}

std::string String::fromBase64(const std::string& base64str, bool acceptFormatting) {
	std::string str;

	std::size_t bufferIndex = 0;
	unsigned char buffer[4];
	bool isNewLineCR = true;
	bool isNewLineLF = true;
	bool hasCharacters = false;

	for(std::size_t pos = 0; pos < base64str.size(); ++pos) {
		// abort if characater base64str[pos] is end symbol
		if(base64str[pos] == '=') {
			break;
		}

		if(acceptFormatting) {
			if(base64str[pos] == 10) {
				if(isNewLineLF) {
					break;
				}
				else {
					isNewLineLF = true;
					continue;
				}
			}
			if(base64str[pos] == 13) {
				if(isNewLineCR) {
					break;
				}
				else {
					isNewLineCR = true;
					continue;
				}
			}

			if(base64str[pos] == ' ' || base64str[pos] == 8) {
				if(hasCharacters) {
					break;
				}
				else {
					isNewLineCR = true;
					isNewLineLF = true;
					continue;
				}
			}
		}

		// abort if characater base64str[pos] is not base64
		if(std::isalnum(base64str[pos]) == 0 && base64str[pos] != '+' && base64str[pos] != '/' && base64str[pos] != '-' && base64str[pos] != '_') {
			break;
		}

		isNewLineCR = false;
		isNewLineLF = false;
		hasCharacters = true;
		buffer[bufferIndex] = base64str[pos];
		++bufferIndex;

		if(bufferIndex==4) {
			str += decodeBase64Buffer(bufferIndex, buffer);
			bufferIndex = 0;
		}
	}

	if(bufferIndex>0) {
		str += decodeBase64Buffer(bufferIndex, buffer);
	}

	return str;
}

std::string String::toURLEncoded(const std::string& str) {
	std::string rv;

	rv.reserve(str.size()*3);

	for(const auto c : str) {
		if(std::isalnum(static_cast<unsigned char>(c)) != 0
		|| static_cast<unsigned char>(c) == '-'
		|| static_cast<unsigned char>(c) == '_'
		|| static_cast<unsigned char>(c) == '.'
		|| static_cast<unsigned char>(c) == '~') {
			rv += c;
		}
		else {
			char buffer[3];
			std::snprintf(buffer, 2, "%02x", static_cast<char>(c));
			rv += '%';
			rv += buffer;
		}
	}

	return rv;
}

std::string String::fromURLEncoded(const std::string& urlEncodedStr) {
	std::string rv;

	rv.reserve(urlEncodedStr.size());

	for(std::size_t i = 0; i < urlEncodedStr.size(); ++i) {
		if(urlEncodedStr[i] != '%') {
			rv += urlEncodedStr[i];
		}
		/* if string ends with '%', then just use this character instead of trying to decode it */
		/* Another option would be to skip this character */
		else if(i+1 == urlEncodedStr.size()) {
			rv += urlEncodedStr[i];
		}
		else {
			std::string part = urlEncodedStr.substr(i+1, i+2 == urlEncodedStr.size() ? 1 : 2);
			char c = std::stoul(part, nullptr, 16);
			rv += c;
		}
	}

	return rv;
}

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */
