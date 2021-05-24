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
#include <esl/io/ReaderString.h>

#include <memory>
#include <cstring>

namespace esl {
namespace io {

ReaderString::ReaderString(std::string aStr)
: str(std::move(aStr))
{ }

std::size_t ReaderString::read(void* data, std::size_t size) {
	if(currentPos >= getSize()) {
		return Reader::npos;
	}


	if(size > getSizeReadable()) {
		size = getSizeReadable();
	}

	std::memcpy(data, getString().data() + currentPos, size);
	currentPos += size;

	return size;
}

std::size_t ReaderString::getSizeReadable() const {
	if(currentPos >= getSize()) {
		return 0;
	}

	return getSize() - currentPos;
}

bool ReaderString::hasSize() const {
	return true;
}

std::size_t ReaderString::getSize() const {
	return getString().size();
}

const std::string& ReaderString::getString() const noexcept {
	return str;
}

} /* namespace io */
} /* namespace esl */
#endif
