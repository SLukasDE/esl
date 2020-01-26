/*
MIT License
Copyright (c) 2019 Sven Lukas

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

#include <esl/utility/StreamBuffer.h>

namespace esl {
namespace utility {

StreamBuffer::StreamBuffer(std::size_t bufferSize, std::function<void(const char*, std::size_t)> writeHandler)
: std::streambuf(),
  bufferSize(bufferSize),
  buffer(bufferSize+1, 0),
  writeHandler(writeHandler)
{
    /* Calling "setp(buffer, buffer)" set space to zero and this results in calling "int_type overflow(int_type c)" */
    setp(&buffer[0], &buffer[0]);
}

StreamBuffer::int_type StreamBuffer::overflow(int_type c) {
    if (c == traits_type::eof()) {
        return traits_type::eof();
    }

    if(epptr() == &buffer[0]) {
        setp(&buffer[0], &buffer[0] + bufferSize - 1);
    }

    *pptr() = c;
    pbump(1);

    if(sync() == -1) {
        return traits_type::eof();
    }

    return c;
}

int StreamBuffer::sync() {
    char* beginStr = pbase();
    char* endStr = pptr();

    if(beginStr == endStr) {
        return 0;
    }

    char* currentStr = beginStr;
    do {
        char currentChar = *currentStr;
        ++currentStr;

        if (currentChar == '\n') {
            std::ptrdiff_t n = currentStr - beginStr;
            writeHandler(beginStr, n);
            beginStr = currentStr;
        }
    } while(currentStr != endStr);

    if (beginStr != currentStr) {
        std::ptrdiff_t n = currentStr - beginStr;
        writeHandler(beginStr, n);
    }

    setp(&buffer[0], &buffer[0] + bufferSize - 1);
    return 0;
}

} /* namespace utility */
} /* namespace esl */
