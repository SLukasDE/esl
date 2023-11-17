/*
 * This file is part of ESL.
 * Copyright (C) 2020-2023 Sven Lukas
 *
 * ESL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ESL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License
 * along with ESL.  If not, see <https://www.gnu.org/licenses/>.
 */

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
