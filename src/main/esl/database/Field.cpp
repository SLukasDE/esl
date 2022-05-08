/*
MIT License
Copyright (c) 2019-2022 Sven Lukas

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

#include <esl/database/Field.h>
#include <esl/database/Column.h>
#include <esl/database/ResultSet.h>
#include <esl/stacktrace/Stacktrace.h>

#include <cctype>
#include <algorithm>
#include <vector>
#include <stdexcept>

namespace esl {
namespace database {

namespace {
Field::Type toFieldType(Column::Type columnType) {
	switch(columnType) {
	case Column::Type::sqlBoolean:
		return Field::Type::storageBoolean;

	case Column::Type::sqlInteger:
	case Column::Type::sqlSmallInt:
		return Field::Type::storageInteger;

	case Column::Type::sqlDouble:
	case Column::Type::sqlNumeric:
	case Column::Type::sqlDecimal:
	case Column::Type::sqlFloat:
	case Column::Type::sqlReal:
		return Field::Type::storageDouble;

	case Column::Type::sqlVarChar:
	case Column::Type::sqlChar:
		return Field::Type::storageString;

	case Column::Type::sqlDateTime:
	case Column::Type::sqlDate:
	case Column::Type::sqlTime:
	case Column::Type::sqlTimestamp:
//	case Column::Type::sqlTimestampWithTimezone:
		return Field::Type::storageString;

//	case Column::Type::sqlRow:
	case Column::Type::sqlWChar:
	case Column::Type::sqlWVarChar:
	case Column::Type::sqlWLongVarChar:
//	case Column::Type::sqlDecFloat:
		return Field::Type::storageString;

	case Column::Type::sqlUnknown:
	default:
		break;
	}

	return Field::Type::storageEmpty;
}

Column::Type toColumnType(Field::Type columnType) {
	switch(columnType) {
	case Field::Type::storageBoolean:
		return Column::Type::sqlBoolean;
	case Field::Type::storageInteger:
		return Column::Type::sqlInteger;
	case Field::Type::storageDouble:
		return Column::Type::sqlDouble;
	case Field::Type::storageString:
		return Column::Type::sqlVarChar;
	case Field::Type::storageEmpty:
	default:
		break;
	}
	return Column::Type::sqlUnknown;
}
}

template<>
std::string Field::toString(bool b) {
	return b ? "true" : "false";
}

template<>
std::string Field::toString(std::int64_t i) {
	return std::to_string(i);
}

template<>
std::string Field::toString(double i) {
	return std::to_string(i);
}

template<>
std::string Field::toString(const std::string& str) {
	return str;
}

template<>
std::int64_t Field::toInteger(bool b) {
	return b ? 1 : 0;
}

template<>
std::int64_t Field::toInteger(std::int64_t i) {
	return i;
}

template<>
std::int64_t Field::toInteger(double i) {
	return static_cast<std::int64_t>(i);
}

template<>
std::int64_t Field::toInteger(const std::string& str) {
	return std::stoll(str);
}

template<>
double Field::toDouble(bool b) {
	return b ? 1 : 0;
}

template<>
double Field::toDouble(std::int64_t i) {
	return i;
}

template<>
double Field::toDouble(double i) {
	return i;
}

template<>
double Field::toDouble(const std::string& str) {
	return std::stod(str);
}

template<>
bool Field::toBoolean(bool b) {
	return b;
}

template<>
bool Field::toBoolean(std::int64_t i) {
	return i != 0;
}

template<>
bool Field::toBoolean(double i) {
	return i >= 0.5 || i <= -0.5;
}

template<>
bool Field::toBoolean(const std::string& str) {
	std::string s;
	std::transform(str.begin(), str.end(), s.begin(),
			[](unsigned char c) { return std::toupper(c); });

	if(s == "TRUE" || s == "-1" || s == "1" || s == "T" || s == "J" || s == "Y" || s == "YES") {
		return true;
	}
	return false;
}

Field::Field(const Field& aField)
: columnType(aField.getColumnType())
{
	if(aField.isNull()) {
		(*this) = nullptr;
	}
	else {
		switch(toFieldType(aField.getColumnType())) {

		case Type::storageBoolean:
			setValue(aField.valueBoolean);
			break;

		case Type::storageInteger:
			setValue(aField.valueInteger);
			break;

		case Type::storageDouble:
			setValue(aField.valueDouble);
			break;

		case Type::storageString:
			setValue(aField.valueString);
			break;

		case Type::storageEmpty:
		default:
			break;
		}
	}
}

Field::Field(Field&& aField)
: resultSet(aField.resultSet),
  columnIndex(aField.columnIndex),
  columnType(aField.columnType),
  valueIsNull(aField.valueIsNull),
  valueBoolean(aField.valueBoolean),
  valueInteger(aField.valueInteger),
  valueDouble(aField.valueDouble),
  valueString(std::move(aField.valueString))
{
	aField.resultSet = nullptr;
	aField.columnIndex = 0;
	aField.columnType = Column::Type::sqlUnknown;
	aField.valueIsNull = true;
}

Field::Field(Column::Type aColumnType)
: columnType(aColumnType)
{ }

Field::Field(ResultSet& aResultSet, std::size_t aColumnIndex)
: resultSet(&aResultSet),
  columnIndex(aColumnIndex)
{
	const Column* column = getColumn();
	if(column) {
		columnType = column->getType();
	}
}

Field::Field(bool value)
: columnType(toColumnType(Type::storageBoolean)),
  valueIsNull(false),
  valueBoolean(value)
{ }

Field::Field(int value)
: columnType(toColumnType(Type::storageInteger)),
  valueIsNull(false),
  valueInteger(value)
{ }

Field::Field(std::int64_t value)
: columnType(toColumnType(Type::storageInteger)),
  valueIsNull(false),
  valueInteger(value)
{ }

Field::Field(double value)
: columnType(toColumnType(Type::storageDouble)),
  valueIsNull(false),
  valueDouble(value)
{ }

Field::Field(const std::string& value)
: columnType(toColumnType(Type::storageString)),
  valueIsNull(false),
  valueString(value)
{ }

Field::Field(const char* value)
: columnType(toColumnType(Type::storageString)),
  valueIsNull(false),
  valueString(value ? value : "")
{ }

Field::operator bool() const {
	return asBoolean();
}

Field::operator int() const {
	return static_cast<int>(asInteger());
}

Field::operator std::int64_t() const {
	return asInteger();
}

Field::operator float() const {
	return static_cast<float>(asDouble());
}

Field::operator double() const {
	return asDouble();
}

Field::operator std::string() const {
	return asString();
}

bool Field::isNull() const {
	return valueIsNull;
}

bool Field::asBoolean() const {
	if(isNull()) {
        throw esl::stacktrace::Stacktrace::add(std::runtime_error("null value"));
	}

	switch(columnType) {
	case Column::Type::sqlBoolean:
		return valueBoolean;

	case Column::Type::sqlInteger:
	case Column::Type::sqlSmallInt:
		return toBoolean(valueInteger);

	case Column::Type::sqlDouble:
	case Column::Type::sqlNumeric:
	case Column::Type::sqlDecimal:
	case Column::Type::sqlFloat:
	case Column::Type::sqlReal:
		return toBoolean(valueDouble);

	case Column::Type::sqlVarChar:
	case Column::Type::sqlChar:
		return toBoolean<const std::string&>(valueString);
	/*{
		const std::string& v(valueString);
		return toBoolean(v);
	}*/

	default:
		break;
	}
	return false;
}

std::int64_t Field::asInteger() const {
	if(isNull()) {
        throw esl::stacktrace::Stacktrace::add(std::runtime_error("null value"));
	}

	switch(columnType) {
	case Column::Type::sqlBoolean:
		return toInteger(valueBoolean);

	case Column::Type::sqlInteger:
	case Column::Type::sqlSmallInt:
		return valueInteger;

	case Column::Type::sqlDouble:
	case Column::Type::sqlNumeric:
	case Column::Type::sqlDecimal:
	case Column::Type::sqlFloat:
	case Column::Type::sqlReal:
		return toInteger(valueDouble);

	case Column::Type::sqlVarChar:
	case Column::Type::sqlChar:
		return toInteger<const std::string&>(valueString);

	default:
		break;
	}
	return 0;
}

double Field::asDouble() const {
	if(isNull()) {
        throw esl::stacktrace::Stacktrace::add(std::runtime_error("null value"));
	}

	switch(columnType) {
	case Column::Type::sqlBoolean:
		return toDouble(valueBoolean);

	case Column::Type::sqlInteger:
	case Column::Type::sqlSmallInt:
		return toDouble(valueInteger);

	case Column::Type::sqlDouble:
	case Column::Type::sqlNumeric:
	case Column::Type::sqlDecimal:
	case Column::Type::sqlFloat:
	case Column::Type::sqlReal:
		return valueDouble;

	case Column::Type::sqlVarChar:
	case Column::Type::sqlChar:
		return toDouble<const std::string&>(valueString);

	default:
		break;
	}
	return 0;
}

std::string Field::asString() const {
	if(isNull()) {
        throw esl::stacktrace::Stacktrace::add(std::runtime_error("null value"));
	}

	switch(columnType) {
	case Column::Type::sqlBoolean:
		return toString(valueBoolean);

	case Column::Type::sqlInteger:
	case Column::Type::sqlSmallInt:
		return toString(valueInteger);

	case Column::Type::sqlDouble:
	case Column::Type::sqlNumeric:
	case Column::Type::sqlDecimal:
	case Column::Type::sqlFloat:
	case Column::Type::sqlReal:
		return toString(valueDouble);

	case Column::Type::sqlVarChar:
	case Column::Type::sqlChar:
		return valueString;

	default:
		break;
	}
	return "";
}

Field& Field::operator=(const Field& aField) {
	if(resultSet == nullptr) {
		columnType = aField.getColumnType();
	}

	if(aField.isNull()) {
		(*this) = nullptr;
	}
	else {
		switch(toFieldType(aField.getColumnType())) {
		case Type::storageBoolean:
			setValue(aField.valueBoolean);
			break;

		case Type::storageInteger:
			setValue(aField.valueInteger);
			break;

		case Type::storageDouble:
			setValue(aField.valueDouble);
			break;

		case Type::storageString:
			setValue(aField.valueString);
			break;

		case Type::storageEmpty:
		default:
			break;
		}
	}
	return *this;
}

Field& Field::operator=(Field&& other) {
	if(&other != this) {
		resultSet = other.resultSet;
		columnIndex = other.columnIndex;
		columnType = other.columnType;
		valueIsNull = other.valueIsNull;
		valueBoolean = other.valueBoolean;
		valueInteger = other.valueInteger;
		valueDouble = other.valueDouble;
		valueString = std::move(other.valueString);

		other.resultSet = nullptr;
		other.columnIndex = 0;
		other.columnType = Column::Type::sqlUnknown;
		other.valueIsNull = true;
	}

	return *this;
}

Field& Field::operator=(std::nullptr_t) {
	if(!valueIsNull) {
		valueIsNull = true;
		if(resultSet) {
			resultSet->setChanged(columnIndex);
		}
	}

	return *this;
}

Field& Field::operator=(bool value) {
	setValueOperator(value);
	return *this;
}

Field& Field::operator=(int value) {
	setValueOperator(static_cast<std::int64_t>(value));
	return *this;
}

Field& Field::operator=(std::int64_t value) {
	setValueOperator(value);
	return *this;
}

Field& Field::operator=(float value) {
	setValueOperator(static_cast<double>(value));
	return *this;
}

Field& Field::operator=(double value) {
	setValueOperator(value);
	return *this;
}

Field& Field::operator=(const std::string& value) {
	setValueOperator<const std::string&>(value);
	return *this;
}

const Column* Field::getColumn() const {
	if(resultSet && resultSet->getColumns()) {
		if(columnIndex >= resultSet->getColumns()->size()) {
	        throw esl::stacktrace::Stacktrace::add(std::out_of_range("internal error: column index = " + std::to_string(columnIndex) + " but result set has only " + std::to_string(resultSet->getColumns()->size()) + " columns"));
		}
		return &(*resultSet->getColumns())[columnIndex];
	}

	return nullptr;
}

Column::Type Field::getColumnType() const {
	return columnType;
}

const std::string& Field::getTypeName() const {
	return Column::toString(columnType);
}

Field::Type Field::getSimpleType() const {
	return toFieldType(columnType);
}

template<>
void Field::setValueOperator(const std::string& value) {
	switch(columnType) {
	case Column::Type::sqlBoolean: {
		setValue(toBoolean<const std::string&>(value));
		break;
	}
	case Column::Type::sqlInteger:
	case Column::Type::sqlSmallInt: {
		setValue(toInteger<const std::string&>(value));
		break;
	}
	case Column::Type::sqlDouble:
	case Column::Type::sqlNumeric:
	case Column::Type::sqlDecimal:
	case Column::Type::sqlFloat:
	case Column::Type::sqlReal: {
		setValue(toDouble<const std::string&>(value));
		break;
	}
	case Column::Type::sqlVarChar:
	case Column::Type::sqlChar: {
		setValue(toString<const std::string&>(value));
		break;
	}
	case Column::Type::sqlUnknown: {
		setValue(value);
		break;
	}
	default:
		break;
	}
}

void Field::setValue(bool value) {
	if(columnType == Column::Type::sqlUnknown) {
		columnType = Column::Type::sqlBoolean;
	}
	else {
		switch(columnType) {
		case Column::Type::sqlBoolean:
			break;
		default:
	        throw esl::stacktrace::Stacktrace::add(std::runtime_error("column is not boolean"));
		}

		if(valueIsNull == false && valueBoolean == value) {
			return;
		}
	}

	valueIsNull = false;
	valueBoolean = value;
	if(resultSet) {
		resultSet->setChanged(columnIndex);
	}
}

void Field::setValue(std::int64_t value) {
	if(columnType == Column::Type::sqlUnknown) {
		columnType = Column::Type::sqlInteger;
	}
	else {
		switch(columnType) {
		case Column::Type::sqlInteger:
		case Column::Type::sqlSmallInt:
			break;
		default:
	        throw esl::stacktrace::Stacktrace::add(std::runtime_error("column is not integer"));
		}

		if(valueIsNull == false && valueInteger == value) {
			return;
		}
	}

	valueIsNull = false;
	valueInteger = value;
	if(resultSet) {
		resultSet->setChanged(columnIndex);
	}
}

void Field::setValue(double value) {
	if(columnType == Column::Type::sqlUnknown) {
		columnType = Column::Type::sqlDouble;
	}
	else {
		switch(columnType) {
		case Column::Type::sqlDouble:
		case Column::Type::sqlNumeric:
		case Column::Type::sqlDecimal:
		case Column::Type::sqlFloat:
		case Column::Type::sqlReal:
			break;
		default:
	        throw esl::stacktrace::Stacktrace::add(std::runtime_error("column is not double"));
		}

		if(valueIsNull == false && valueDouble == value) {
			return;
		}
	}

	valueIsNull = false;
	valueDouble = value;
	if(resultSet) {
		resultSet->setChanged(columnIndex);
	}
}

void Field::setValue(const std::string& value) {
	if(columnType == Column::Type::sqlUnknown) {
		columnType = Column::Type::sqlVarChar;
	}
	else {
		switch(columnType) {
		case Column::Type::sqlVarChar:
		case Column::Type::sqlChar:
			break;
		default:
	        throw esl::stacktrace::Stacktrace::add(std::runtime_error("column is not string"));
		}

		if(valueIsNull == false && valueString == value) {
			return;
		}
	}

	valueIsNull = false;
	valueString = value;
	if(resultSet) {
		resultSet->setChanged(columnIndex);
	}
}

} /* namespace database */
} /* namespace esl */
