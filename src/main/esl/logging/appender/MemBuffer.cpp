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

#include <esl/logging/appender/MemBuffer.h>

namespace esl {
namespace logging {
namespace appender {

MemBuffer::MemBuffer(std::size_t maxRows, std::size_t maxColumns)
: Appender(),
  locations(maxRows+1),
  maxRows(maxRows+1),
  maxColumns(maxColumns)
{
	if(maxColumns == 0) {
	    std::vector<std::string> tmpLines(maxRows+1);
		lines = std::move(tmpLines);
	}
	else {
		std::vector<LineBuffer> tmpRows(maxRows+1, LineBuffer(maxColumns+1, 0));
		rows = std::move(tmpRows);
	}
}

MemBuffer::~MemBuffer() {
}

std::vector<std::tuple<Location, std::string>> MemBuffer::getBuffer() const {
	std::vector<std::tuple<Location, std::string>> rv;

	if(maxColumns == 0) {
		for(std::size_t tmpIdxCons = rowConsumer; tmpIdxCons != rowProducer; tmpIdxCons = (tmpIdxCons + 1) % maxRows) {
	    	rv.push_back(std::make_tuple(locations[tmpIdxCons], lines[tmpIdxCons]));
	    }
	}
	else {
		for(std::size_t tmpIdxCons = rowConsumer; tmpIdxCons != rowProducer; tmpIdxCons = (tmpIdxCons + 1) % maxRows) {
	    	rv.push_back(std::make_tuple(locations[tmpIdxCons], std::string(&rows[tmpIdxCons][0])));
	    }
	}

	return rv;
}

void MemBuffer::flushNewLine(const Location& location, bool enabled) {
	switch(getRecordLevel()) {
	case RecordLevel::OFF:
		return;
	case RecordLevel::ALL:
		break;
	default: /* RecordLevel::SELECTED */
		if(!enabled) {
			return;
		}
		break;
	}

	if(columnsProducer > 0) {
        rowProducer = (rowProducer + 1) % maxRows;
        if(maxColumns == 0) {
            lines[rowProducer].clear();
        }
        else {
            rows[rowProducer][0] = 0;
        }
        columnsProducer = 0;
        if(rowConsumer == rowProducer) {
            rowConsumer = (rowConsumer + 1) % maxRows;
        }
	}
}

void MemBuffer::write(const Location& location, bool enabled, const char* str, std::size_t len) {
	switch(getRecordLevel()) {
	case RecordLevel::OFF:
		return;
	case RecordLevel::ALL:
		break;
	default: /* RecordLevel::SELECTED */
		if(!enabled) {
			return;
		}
		break;
	}

    while(len > 0) {
        bool lineWritten = false;

        locations[rowProducer] = location;

        for(std::size_t i = 0; i < len; ++i) {
            if(str[i] != '\n') {
                continue;
            }

            if(maxColumns == 0) {
            	lines[rowProducer] += std::string(str, i);
            }
            else {
                std::strncat(&rows[rowProducer][columnsProducer], str, std::min(i, maxColumns - columnsProducer));
            }

            lineWritten = true;
            rowProducer = (rowProducer + 1) % maxRows;
            columnsProducer = 0;

            if(maxColumns == 0) {
            	lines[rowProducer].clear();
            }
            else {
                rows[rowProducer][0] = 0;
            }

            if(rowConsumer == rowProducer) {
                rowConsumer = (rowConsumer + 1) % maxRows;
            }

            ++i;
            str += i;
            len -= i;
            break;
        }

        if(!lineWritten) {
            if(maxColumns == 0) {
            	lines[rowProducer] += std::string(str, len);
                columnsProducer += len;
            }
            else {
                std::strncat(&rows[rowProducer][columnsProducer], str, std::min(len, maxColumns - columnsProducer));
                columnsProducer += std::min(len, maxColumns - columnsProducer);
            }

            len = 0;
        }
    }
}

} /* namespace appender */
} /* namespace logging */
} /* namespace esl */
