/*
MIT License
Copyright (c) 2019-2025 Sven Lukas

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

#ifndef ESL_DATABASE_PREPAREDSTATEMENT_H_
#define ESL_DATABASE_PREPAREDSTATEMENT_H_

#include <esl/database/Column.h>
#include <esl/database/ResultSet.h>
#include <esl/database/Field.h>

#include <vector>
#include <memory>

namespace esl {
inline namespace v1_6 {
namespace database {

class PreparedStatement {
public:
	class Binding {
	public:
		virtual ~Binding() = default;

		virtual const std::vector<Column>& getParameterColumns() const = 0;
		virtual const std::vector<Column>& getResultColumns() const = 0;
		virtual ResultSet execute(const std::vector<Field>& fields) = 0;
		virtual void* getNativeHandle() const = 0;
	};

	PreparedStatement() = default;
	PreparedStatement(const PreparedStatement&) = delete;
	PreparedStatement(PreparedStatement&&) = default;
	PreparedStatement(std::unique_ptr<Binding> binding);

	~PreparedStatement() = default;

	explicit operator bool() const noexcept;

	PreparedStatement& operator=(const PreparedStatement&) = delete;
	PreparedStatement& operator=(PreparedStatement&& other) = default;

	const std::vector<Column>& getParameterColumns() const;
	const std::vector<Column>& getResultColumns() const;

	ResultSet execute(const std::vector<Field>& fields);

	ResultSet execute();

    template<typename... Args>
	ResultSet execute(Args... args) {
	    std::vector<Field> fields;
	    addArguments(fields, args...);
	    return execute(fields);
    }

	void* getNativeHandle() const;

private:
	template<typename T>
	static inline void addArguments(std::vector<Field>& fields, const T& t) {
		Field field(t);
		fields.push_back(field);
	}

	template<typename T, typename... Args>
	static inline void addArguments(std::vector<Field>& fields, const T& t, Args... args) {
    	Field field(t);
    	fields.push_back(field);
    	addArguments(fields, args...);
	}

	template<typename T>
	static inline void addArrayArguments(std::vector<std::vector<Field>>& fieldArrays, const T& tArray) {
		std::vector<Field> fieldArray;
		for(const auto& t : tArray) {
			Field field(t);
			fieldArray.push_back(field);
		}
		fieldArrays.push_back(fieldArray);
	}

	template<typename T, typename... Args>
	static inline void addArrayArguments(std::vector<std::vector<Field>>& fieldArrays, const T& tArray, Args... args) {
		std::vector<Field> fieldArray;
		for(const auto& t : tArray) {
			Field field(t);
			fieldArray.push_back(field);
		}
		fieldArrays.push_back(fieldArray);
    	addArrayArguments(fieldArrays, args...);
	}

	std::unique_ptr<Binding> binding;
};

} /* namespace database */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_DATABASE_PREPAREDSTATEMENT_H_ */
