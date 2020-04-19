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

#ifndef ESL_DATABASE_RESULTSET_H_
#define ESL_DATABASE_RESULTSET_H_

#include <esl/database/Column.h>
#include <esl/database/Field.h>
#include <cstddef>
#include <string>
#include <map>
#include <vector>
#include <memory>

namespace esl {
namespace database {

class ResultSet {
	friend class Field;
public:
	class Binding {
	public:
		Binding(const std::vector<Column>& columns);
		virtual ~Binding() = default;

		const std::vector<Column>& getColumns() const;

		virtual bool fetch(std::vector<Field>& fields) = 0;
		virtual bool isEditable(std::size_t columnIndex) = 0;
		virtual void add(std::vector<Field>& fields) = 0;
		virtual void save(std::vector<Field>& fields) = 0;

	private:
		const std::vector<Column> columns;
	};

	ResultSet() = default;
	ResultSet(const ResultSet&) = delete;
	ResultSet(ResultSet&& recordSet);
	ResultSet(std::unique_ptr<Binding> binding);

	explicit operator bool() const noexcept;

	ResultSet& operator=(const ResultSet&) = delete;
	ResultSet& operator=(ResultSet&& other);

	const Field& operator[](const std::string& name) const;
	Field& operator[](const std::string& name);

	const Field& operator[](std::size_t index) const;
	Field& operator[](std::size_t index);

	std::size_t size() const;
	const std::vector<Column>* getColumns() const;

	void next();
	void add();
	void save();

private:
	void setChanged(std::size_t index);

	std::unique_ptr<Binding> binding;
	std::vector<Field> fields;
	std::map<std::string, std::size_t> nameToIndex;
	bool valuesChanged = false;
};

} /* namespace database */
} /* namespace esl */

#endif /* ESL_DATABASE_RESULTSET_H_ */
