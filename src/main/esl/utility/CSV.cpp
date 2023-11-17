#include <esl/utility/CSV.h>
#include <esl/utility/String.h>

#include <utility>
#include <functional>

namespace esl {
inline namespace v1_6 {
namespace utility {

CSV::CSV(char aSeparator)
: separator(aSeparator)
{ }

std::vector<std::string> CSV::splitRow(const std::string& row) {
	std::vector<std::string> columns;
	std::string column;

    bool escapeState = false;

    for(auto const& c : row) {
        if(c == separator && !escapeState) {
        	columns.push_back(column);
        	columns.clear();
        	escapeState = false;
            continue;
        }

        column += c;
        if(c == '\\' && !escapeState) {
        	escapeState = true;
        } else {
        	escapeState = false;
        }
    }

    columns.push_back(column);

    return columns;
}

std::string CSV::toRow(const std::vector<std::string>& columns) {
	std::string row;
	bool isFirstColumn = true;

	for(const auto& column : columns) {
		if(!isFirstColumn) {
			row += separator;
		}

		row += String::toEscape(column, [this](char c) {
			std::string result;

			if(c == separator) {
				result = std::string(1, separator);
			}
			result += c;

			return result;
		});

		isFirstColumn = false;
	}

	return row;
}

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */
