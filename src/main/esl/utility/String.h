#ifndef ESL_UTILITY_STRING_H_
#define ESL_UTILITY_STRING_H_

#include <functional>
#include <set>
#include <string>
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
	static int toInt(const std::string& str);
	static long toLong(const std::string& str);

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
	static std::string toBase64(const std::string& str, Base64Variant base64Variant = base64url, bool withPadding = false);
	static std::string fromBase64(const std::string& base64str, bool acceptFormatting = false);
};

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_STRING_H_ */
