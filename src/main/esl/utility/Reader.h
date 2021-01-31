/*
MIT License
Copyright (c) 2019-2021 Sven Lukas

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

#ifndef ESL_UTILITY_READER_H_
#define ESL_UTILITY_READER_H_

#include <string>

namespace esl {
namespace utility {

class Reader {
public:
	static const std::size_t npos = static_cast<std::size_t>(-1);

	Reader() = default;
	virtual ~Reader() = default;

	// returns npos if no more data is available.
	// otherwise it returns the number of bytes that have been read.
	virtual std::size_t read(void* data, std::size_t size) = 0;

	// returns available bytes that can be read with next call of read(...).
	// npos is returned if available size is unknown.
	// 0 just means, that there are currently no bytes available and read() would return as well 0.
	// 0 does NOT mean, that there are no more bytes available in general.
	virtual std::size_t getSizeReadable() const {
		return npos;
	}

};

} /* namespace utility */
} /* namespace esl */

#endif /* ESL_UTILITY_READER_H_ */
