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

#ifndef ESL_DATABASE_COLUMN_H_
#define ESL_DATABASE_COLUMN_H_

#include <string>

namespace esl {
namespace database {

class Column {
public:
	enum class Type {
		sqlBoolean,

		sqlInteger,
		sqlSmallInt,

		sqlDouble,
		sqlNumeric,
		sqlDecimal,
		sqlFloat,
		sqlReal,

		sqlVarChar,
		sqlChar,

		sqlDateTime,
		sqlDate,
		sqlTime,
		sqlTimestamp,
		sqlTimestampWithTimezone,

		sqlRow,
		sqlWChar,
		sqlWVarChar,
		sqlWLongVarChar,
		sqlDecFloat,

		sqlUnknown
	};

	Column(std::string name, Type type, unsigned int characterLength, unsigned int decimalDigits, bool nullable, unsigned int displayLength);

	const std::string& getName() const;
	Type getType() const;

	const std::string& getTypeName() const;
	bool isNullable() const;
	unsigned int getCharacterLength() const;
	unsigned int getDecimalDigits() const;
	unsigned int getDisplayLength() const;

private:
	std::string name;
	Type type = Type::sqlUnknown;

	unsigned int characterLength;
	unsigned int decimalDigits;
	bool nullable;
	unsigned int displayLength;
};

} /* namespace database */
} /* namespace esl */

#endif /* ESL_DATABASE_COLUMN_H_ */
