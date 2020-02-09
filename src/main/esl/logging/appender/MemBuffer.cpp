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
  entries(maxRows+1, (maxColumns > 0 ? maxColumns : 0)),
  maxRows(maxRows+1),
  maxColumns(maxColumns)
{
}

MemBuffer::~MemBuffer() {
}

std::vector<std::tuple<Location, std::string>> MemBuffer::getBuffer() const {
	std::vector<std::tuple<Location, std::string>> rv;

	if(maxColumns > 0) {
		for(std::size_t tmpIdxCons = rowConsumer; tmpIdxCons != rowProducer; tmpIdxCons = (tmpIdxCons + 1) % maxRows) {
	    	rv.push_back(std::make_tuple(entries[tmpIdxCons].location, std::string(&entries[tmpIdxCons].lineStaticSize[0])));
		}
	}
	else {
		for(std::size_t tmpIdxCons = rowConsumer; tmpIdxCons != rowProducer; tmpIdxCons = (tmpIdxCons + 1) % maxRows) {
	    	rv.push_back(std::make_tuple(entries[tmpIdxCons].location, entries[tmpIdxCons].lineDynamicSize));
		}
	}

	return rv;
}

void MemBuffer::flush() {
}

void MemBuffer::write(const Location& location, const char* str, std::size_t len) {
	switch(getRecordLevel()) {
	case RecordLevel::OFF:
		return;
	case RecordLevel::ALL:
		break;
	default: /* RecordLevel::SELECTED */
		if(!location.enabled) {
			return;
		}
		break;
	}

	if(entries[rowProducer].location != location) {
		if(columnsProducer > 0) {
			newline();
		}
    	entries[rowProducer].location = location;
	}

	const char* begin = str;

	for(auto iter = str; iter != &str[len]; ++iter) {
		if(*iter == '\n') {
            write(begin, iter-begin);
            newline();
        	entries[rowProducer].location = location;
			begin = iter+1;
		}
	}
}

void MemBuffer::write(const char* ptr, std::size_t size) {
    if(maxColumns == 0) {
    	entries[rowProducer].lineDynamicSize += std::string(ptr, size);
        columnsProducer += size;
    }
    else {
        std::strncat(&entries[rowProducer].lineStaticSize[columnsProducer], ptr, std::min(size, maxColumns - columnsProducer));
        columnsProducer += std::min(size, maxColumns - columnsProducer);
    }
}

void MemBuffer::newline() {
    rowProducer = (rowProducer + 1) % maxRows;
    if(rowConsumer == rowProducer) {
        rowConsumer = (rowConsumer + 1) % maxRows;
    }

    if(maxColumns == 0) {
    	entries[rowProducer].lineDynamicSize.clear();
    }
    else {
    	entries[rowProducer].lineStaticSize[0] = 0;
    }
    columnsProducer = 0;
}

} /* namespace appender */
} /* namespace logging */
} /* namespace esl */
