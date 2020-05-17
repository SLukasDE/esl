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

	//Column(std::string name, Type type, bool nullable, std::size_t characterLength, std::size_t decimalDigits, std::size_t displayLength);
	Column(std::string name, Type type, bool nullable, std::size_t defaultBufferSize, std::size_t maximumBufferSize, std::size_t decimalDigits, std::size_t characterLength, std::size_t displayLength);

	/* column name as result of the underlying SQL statement */
	const std::string& getName() const;

	/* type of this column as result of the underlying SQL statement */
	Type getType() const;

	/* translates type to a string */
	const std::string& getTypeName() const;

	/* returns true if this column is able to store NULL value */
	bool isNullable() const;

	/* returns 0 if value has to be fetched manually */
	std::size_t getBufferSize() const;
	std::size_t getDefaultBufferSize() const;

	/* other meta data about this column */
	std::size_t getCharacterLength() const;
	std::size_t getDecimalDigits() const;
	std::size_t getDisplayLength() const;

private:
	std::string name;
	Type type = Type::sqlUnknown;

	bool nullable;
	std::size_t defaultBufferSize;
	std::size_t maximumBufferSize;
	std::size_t characterLength;
	std::size_t decimalDigits;
	std::size_t displayLength;
};

} /* namespace database */
} /* namespace esl */

#endif /* ESL_DATABASE_COLUMN_H_ */
