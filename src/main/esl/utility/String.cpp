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
}

std::vector<std::string> String::split(const std::string& str, const char separator) {
    std::vector<std::string> rv;
    std::string::const_iterator currentIt = str.begin();
    std::string::const_iterator lastIt = currentIt;

    for(;currentIt != str.end(); ++currentIt) {
        if(*currentIt == separator) {
            rv.push_back( std::string(lastIt, currentIt));
            lastIt = currentIt;
            ++lastIt;
        }
    }
    rv.push_back(std::string(lastIt, currentIt));

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

} /* namespace utility */
} /* namespace esl */
