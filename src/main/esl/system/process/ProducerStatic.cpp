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

#include <esl/system/process/ProducerStatic.h>

namespace esl {
namespace system {
namespace process {

ProducerStatic::ProducerStatic(const char* aData, std::size_t aSize)
: data(aData),
  size(aSize)
{ }

std::size_t ProducerStatic::write(utility::Writer& writer) {
	std::size_t count = writer.write(getData(), getSize() - currentPos);

	if(count != 0) {
		if(count == utility::Writer::npos) {
			/* error occurred. set currentPos to the end of the content */
			currentPos = getSize();
		}
		else {
			currentPos += count;
		}
	}

	return (currentPos < getSize()) ? count : utility::Writer::npos;
}

const char* ProducerStatic::getData() const noexcept {
	return data;
}

std::size_t ProducerStatic::getSize() const noexcept {
	return size;
}

} /* namespace process */
} /* namespace system */
} /* namespace esl */
