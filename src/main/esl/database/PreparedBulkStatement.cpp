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


#include <esl/database/PreparedBulkStatement.h>
#include <esl/monitoring/Streams.h>
#include <esl/monitoring/Logger.h>

namespace esl {
inline namespace v1_6 {
namespace database {
namespace {
std::vector<Column> emptyColumns;
monitoring::Logger<monitoring::Streams::Level::trace> logger("esl::database::PreparedBulkStatement");
}

PreparedBulkStatement::PreparedBulkStatement(std::unique_ptr<Binding> aBinding)
: binding(std::move(aBinding))
{ }

PreparedBulkStatement::operator bool() const noexcept {
	return binding ? true : false;
}

const std::vector<Column>& PreparedBulkStatement::getParameterColumns() const {
	if(binding) {
		return binding->getParameterColumns();
	}
	return emptyColumns;
}

PreparedBulkStatement& PreparedBulkStatement::execute(const std::vector<Field>& fields) {
	if(binding) {
		binding->execute(fields);
	}
	return *this;
}

void* PreparedBulkStatement::getNativeHandle() const {
	if(binding) {
		return binding->getNativeHandle();
	}
	return nullptr;
}

} /* namespace database */
} /* inline namespace v1_6 */
} /* namespace esl */
