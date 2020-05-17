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

#include <esl/database/Column.h>

#include <limits>

namespace esl {
namespace database {

namespace {
const std::string typeNameBoolean = "SQL_BOOLEAN";

const std::string typeNameInteger = "SQL_INTEGER";
const std::string typeNameSmallInt = "SQL_SMALLINT";

const std::string typeNameDouble = "SQL_DOUBLE";
const std::string typeNameNumeric = "SQL_NUMERIC";
const std::string typeNameDecimal = "SQL_DECIMAL";
const std::string typeNameFloat = "SQL_FLOAT";
const std::string typeNameReal = "SQL_REAL";

const std::string typeNameVarChar = "SQL_VARCHAR";
const std::string typeNameChar = "SQL_CHAR";

const std::string typeNameDateTime = "SQL_DATETIME";
const std::string typeNameDate = "SQL_TYPE_DATE";
const std::string typeNameTime = "SQL_TYPE_TIME";
const std::string typeNameTimestamp = "SQL_TYPE_TIMESTAMP";
const std::string typeNameTimestampWithTimezone = "SQL_TYPE_TIMESTAMP_WITH_TIMEZONE";

const std::string typeNameRow = "SQL_ROW";
const std::string typeNameWChar = "SQL_WCHAR";
const std::string typeNameWVarChar = "SQL_WVARCHAR";
const std::string typeNameWLongVarChar = "SQL_WLONGVARCHAR";
const std::string typeNameDecFloat = "SQL_DECFLOAT";

const std::string typeNameUnknown = "unknown";

const std::string& columnType2String(Column::Type columnType) {
	switch(columnType) {
	case Column::Type::sqlBoolean:
		return typeNameBoolean;

	case Column::Type::sqlInteger:
		return typeNameInteger;
	case Column::Type::sqlSmallInt:
		return typeNameSmallInt;

	case Column::Type::sqlDouble:
		return typeNameDouble;
	case Column::Type::sqlNumeric:
		return typeNameNumeric;
	case Column::Type::sqlDecimal:
		return typeNameDecimal;
	case Column::Type::sqlFloat:
		return typeNameFloat;
	case Column::Type::sqlReal:
		return typeNameReal;

	case Column::Type::sqlVarChar:
		return typeNameVarChar;
	case Column::Type::sqlChar:
		return typeNameChar;

	case Column::Type::sqlDateTime:
		return typeNameDateTime;
	case Column::Type::sqlDate:
		return typeNameDate;
	case Column::Type::sqlTime:
		return typeNameTime;
	case Column::Type::sqlTimestamp:
		return typeNameTimestamp;
	case Column::Type::sqlTimestampWithTimezone:
		return typeNameTimestampWithTimezone;

	case Column::Type::sqlRow:
		return typeNameRow;
	case Column::Type::sqlWChar:
		return typeNameWChar;
	case Column::Type::sqlWVarChar:
		return typeNameWVarChar;
	case Column::Type::sqlWLongVarChar:
		return typeNameWLongVarChar;
	case Column::Type::sqlDecFloat:
		return typeNameDecFloat;
	default:
		break;
	}

	return typeNameUnknown;
}

} /* anonymous namespace */

Column::Column(std::string aName, Column::Type aType, bool aNullable, std::size_t aDefaultBufferSize, std::size_t aMaximumBufferSize, std::size_t aDecimalDigits, std::size_t aCharacterLength, std::size_t aDisplayLength)
: name(std::move(aName)),
  type(aType),
  nullable(aNullable),
  defaultBufferSize(aDefaultBufferSize),
  maximumBufferSize((aMaximumBufferSize > 0 && aMaximumBufferSize < aDefaultBufferSize) ? aDefaultBufferSize : aMaximumBufferSize),
  characterLength(aCharacterLength),
  decimalDigits(aDecimalDigits),
  displayLength(aDisplayLength)
{ }

const std::string& Column::getName() const {
	return name;
}

Column::Type Column::getType() const {
	return type;
}

const std::string& Column::getTypeName() const {
	return columnType2String(getType());
}

bool Column::isNullable() const {
	return nullable;
}

std::size_t Column::getBufferSize() const {
	std::size_t valueBufferSize = std::max(getCharacterLength(), getDisplayLength());

	if(valueBufferSize >= std::numeric_limits<std::size_t>::max()) {
		valueBufferSize = defaultBufferSize;
	}

	if(maximumBufferSize > 0 && maximumBufferSize < valueBufferSize) {
		valueBufferSize = defaultBufferSize;
	}

	return valueBufferSize;
}

std::size_t Column::getDefaultBufferSize() const {
	return defaultBufferSize;
}

std::size_t Column::getCharacterLength() const {
	return characterLength;
}

std::size_t Column::getDecimalDigits() const {
	return decimalDigits;
}

std::size_t Column::getDisplayLength() const {
	return displayLength;
}

} /* namespace database */
} /* namespace esl */
