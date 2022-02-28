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

#include <esl/utility/CSV.h>
#include <esl/utility/String.h>

#include <utility>
#include <functional>

namespace esl {
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
} /* namespace esl */
