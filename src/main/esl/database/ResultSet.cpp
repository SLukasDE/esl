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

#include <esl/database/ResultSet.h>
#include <esl/database/PreparedStatement.h>
#include <esl/database/exception/RuntimeError.h>
#include <esl/Stacktrace.h>

namespace esl {
namespace database {

ResultSet::Binding::Binding(const std::vector<Column>& aColumns)
: columns(aColumns)
{
}

const std::vector<Column>& ResultSet::Binding::getColumns() const {
	return columns;
}

ResultSet::ResultSet(ResultSet&& other)
: binding(std::move(other.binding)),
  fields(std::move(other.fields)),
  nameToIndex(std::move(other.nameToIndex)),
  valuesChanged(other.valuesChanged)
{
	for(auto& field : fields) {
		field.resultSet = this;
	}
	//other.fields.clear();
	//other.nameToIndex.clear();
	other.valuesChanged = false;
}

ResultSet::ResultSet(std::unique_ptr<ResultSet::Binding> aBinding)
: binding(std::move(aBinding))
{
	if(binding) {
		const std::vector<Column>& columns = binding->getColumns();

		fields.resize(columns.size());
		for(std::size_t i=0; i<columns.size(); ++i) {
			nameToIndex[columns[i].getName()] = i;
			fields[i] = Field(*this, i);
		}

		next();
	}

}

ResultSet::operator bool() const noexcept {
	return binding ? true : false;
}

ResultSet& ResultSet::operator=(ResultSet&& other) {
	if(this != &other) {
		binding = std::move(other.binding);
		fields = std::move(other.fields);
		for(auto& field : fields) {
			field.resultSet = this;
		}
		nameToIndex = std::move(other.nameToIndex);
		valuesChanged = other.valuesChanged;

		//other.fields.clear();
		//other.nameToIndex.clear();
		other.valuesChanged = false;
	}
	return *this;
}

const Field& ResultSet::operator[](const std::string& name) const {
	if(!binding) {
        throw esl::addStacktrace(exception::RuntimeError(std::string("cannot access field \"") + name + "\" because record set it empty."));
	}

	auto iter = nameToIndex.find(name);
	if(iter == nameToIndex.end()) {
        throw esl::addStacktrace(exception::RuntimeError(std::string("unknown field \"") + name + "\" requested."));
	}
	return fields[iter->second];
}

Field& ResultSet::operator[](const std::string& name) {
	if(!binding) {
        throw esl::addStacktrace(exception::RuntimeError(std::string("cannot access field \"") + name + "\" because record set it empty."));
	}

	auto iter = nameToIndex.find(name);
	if(iter == nameToIndex.end()) {
        throw esl::addStacktrace(exception::RuntimeError(std::string("unknown field \"") + name + "\" requested."));
	}
	return fields[iter->second];
}

const Field& ResultSet::operator[](std::size_t index) const {
	if(!binding) {
        throw esl::addStacktrace(exception::RuntimeError(std::string("cannot access field at index \"") + std::to_string(index) + "\" because record set it empty."));
	}

	return fields[index];
}

Field& ResultSet::operator[](std::size_t index) {
	if(!binding) {
        throw esl::addStacktrace(exception::RuntimeError(std::string("cannot access field at index \"") + std::to_string(index) + "\" because record set it empty."));
	}

	return fields[index];
}

std::size_t ResultSet::size() const {
	if(!binding) {
		binding->getColumns().size();
	}
	return 0;
}

const std::vector<Column>* ResultSet::getColumns() const {
	if(!binding) {
		return &binding->getColumns();
	}
	return nullptr;

}

void ResultSet::next() {
	if(!binding) {
        throw esl::addStacktrace(exception::RuntimeError("cannot go to next result set because result set is already at the end."));
	}

	save();
	std::unique_ptr<Binding> tmpBinding = std::move(binding);
	if(tmpBinding->fetch(fields)) {
		binding = std::move(tmpBinding);
	}
	valuesChanged = false;
}

void ResultSet::add() {
	if(!binding) {
        throw esl::addStacktrace(exception::RuntimeError("cannot add a new row because result set is already at the end."));
	}

	save();
	binding->add(fields);
}

void ResultSet::save() {
	if(!valuesChanged) {
		return;
	}

	if(!binding) {
        throw esl::addStacktrace(exception::RuntimeError("cannot save current result set because it is already at the end."));
	}

	binding->save(fields);
	valuesChanged = false;
}

void ResultSet::setChanged(std::size_t index) {
	if(binding && binding->isEditable(index) == false) {
        throw esl::addStacktrace(exception::RuntimeError("cannot edit field."));
	}
	valuesChanged = true;
}

} /* namespace database */
} /* namespace esl */
