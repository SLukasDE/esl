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

#ifndef SRC_MAIN_C___ESL_UTILITY_STRING_H_
#define SRC_MAIN_C___ESL_UTILITY_STRING_H_

#include <string>
#include <vector>
#include <functional>

namespace esl {
namespace utility {

class String {
public:
	static std::vector<std::string> split(const std::string& str, const char separator);

	static std::string ltrim(std::string str, char trimCharacter = ' ');
	static std::string rtrim(std::string str, char trimCharacter = ' ');
	static std::string trim(std::string str, char trimCharacter = ' ');

	static std::string toUpper(std::string str);
	static std::string toLower(std::string str);

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

private:
	String() = default;
	~String() = default;
};

} /* namespace utility */
} /* namespace esl */

#endif /* SRC_MAIN_C___ESL_UTILITY_STRING_H_ */
