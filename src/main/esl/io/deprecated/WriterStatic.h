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

#if 0
#ifndef ESL_IO_OUTPUT_WRITERSTATIC_H_
#define ESL_IO_OUTPUT_WRITERSTATIC_H_

#include <esl/io/Writer.h>

#include <string>

namespace esl {
namespace io {
namespace output {

class WriterStatic : public Writer {
public:
	WriterStatic(void* data, std::size_t size);

	std::size_t write(const void* data, std::size_t size) override;

	std::size_t getSizeWritable() const override;

private:

	void* bufferData;
	std::size_t bufferSize;
	std::size_t currentPos = 0;
};

} /* namespace output */
} /* namespace io */
} /* namespace esl */

#endif /* ESL_IO_OUTPUT_WRITERSTATIC_H_ */
#endif
