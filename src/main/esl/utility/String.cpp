/*
MIT License
Copyright (c) 2019-2021 Sven Lukas

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

#include <esl/utility/String.h>

#include <map>
#include <utility>
#include <algorithm>
#include <iterator>
#include <cctype>

namespace esl {
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

/*
std::string &String::ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}
*/
std::string String::ltrim(std::string str, char trimCharacter) {
    str.erase(std::begin(str), std::find_if(std::begin(str), std::end(str), [trimCharacter](int c) {
        return c != trimCharacter;
    }));

    return str;
}

/*
std::string &String::rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}
*/
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

std::string String::toBase64(const std::string& str, Base64Variant base64Variant) {
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
			else {
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

std::string String::fromBase64(const std::string& base64str) {
	std::string str;

	std::size_t bufferIndex = 0;
	unsigned char buffer[4];

	for(std::size_t pos = 0; pos < base64str.size(); ++pos) {
		// abort if characater base64str[pos] is end symbol
		if(base64str[pos] == '=') {
			break;
		}
		// abort if characater base64str[pos] is not base64
		if(std::isalnum(base64str[pos]) == 0 && base64str[pos] != '+' && base64str[pos] != '/' && base64str[pos] != '-' && base64str[pos] != '_') {
			break;
		}

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

} /* namespace utility */
} /* namespace esl */
