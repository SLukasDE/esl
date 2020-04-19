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

#ifndef ESL_DATABASE_FIELD_H_
#define ESL_DATABASE_FIELD_H_

#include <esl/database/Column.h>
#include <cstdint>
#include <cstddef>
#include <string>

namespace esl {
namespace database {

class ResultSet;
class Column;

class Field {
	friend class ResultSet;
public:
	enum class Type {
		storageBoolean,
		storageInteger,
		storageDouble,
		storageString,
		storageEmpty
	};

	Field() = default;
	Field(const Field&);
	Field(Column::Type columnType);
	Field(ResultSet& resultSet, std::size_t columnIndex);
	Field(bool value);
	Field(int value);
	Field(std::int64_t value);
	Field(double value);
	Field(const std::string& value);
	Field(const char* value);


	explicit operator bool() const;
	explicit operator int() const;
	explicit operator std::int64_t() const;
	explicit operator float() const;
	explicit operator double() const;
	explicit operator std::string() const;

	bool isNull() const;
	bool asBoolean() const;
	std::int64_t asInteger() const;
	double asDouble() const;
	std::string asString() const;

	Field& operator=(const Field&);
	Field& operator=(std::nullptr_t);
	Field& operator=(bool value);
	Field& operator=(int value);
	Field& operator=(std::int64_t value);
	Field& operator=(float value);
	Field& operator=(double value);
	Field& operator=(const std::string& value);

	const Column* getColumn() const;
	Column::Type getColumnType() const;

	Type getType() const;

private:
	Field(Field&& field);
	Field& operator=(Field&& other);

	template<typename T>
	static std::string toString(T t);

	template<typename T>
	static std::int64_t toInteger(T t);

	template<typename T>
	static double toDouble(T t);

	template<typename T>
	static bool toBoolean(T t);

	template<typename T>
	void setValueOperator(T value) {
		switch(columnType) {
		case Column::Type::sqlBoolean: {
			setValue(toBoolean(value));
			break;
		}
		case Column::Type::sqlInteger:
		case Column::Type::sqlSmallInt: {
			setValue(toInteger(value));
			break;
		}
		case Column::Type::sqlDouble:
		case Column::Type::sqlNumeric:
		case Column::Type::sqlDecimal:
		case Column::Type::sqlFloat:
		case Column::Type::sqlReal: {
			setValue(toDouble(value));
			break;
		}
		case Column::Type::sqlVarChar:
		case Column::Type::sqlChar: {
			setValue(toString(value));
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

	void setValue(bool value);
	void setValue(std::int64_t value);
	void setValue(double value);
	void setValue(const std::string& value);

	ResultSet* resultSet = nullptr;
	std::size_t columnIndex = 0;
	Column::Type columnType = Column::Type::sqlUnknown;

	bool valueIsNull = true;

	bool valueBoolean = false;
	std::int64_t valueInteger = 0;
	double valueDouble = 0;
	std::string valueString;
};

template<>
void Field::setValueOperator(const std::string& value);

} /* namespace database */
} /* namespace esl */

#endif /* ESL_DATABASE_FIELD_H_ */
