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

#include <esl/utility/String.h>
#include <utility>
#include <algorithm>

namespace esl {
namespace utility {

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

} /* namespace utility */
} /* namespace esl */
