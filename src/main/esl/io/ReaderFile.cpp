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

#include <esl/io/ReaderFile.h>
#include <esl/logging/Logger.h>

namespace esl {
namespace io {

namespace {
logging::Logger<> logger("esl::io::ReaderFile");
}

ReaderFile::ReaderFile(const std::string& filename)
: file(new std::ifstream(filename))
{
	if(file->good()) {
		const auto begin = file->tellg();
		file->seekg(0, std::ios::end);
		const auto end = file->tellg();
		size = (end-begin);
	}
	else {
        logger.warn << "esl: cannot open file \"" << filename << "\"\n";
        file.reset();
	}
}

std::size_t ReaderFile::read(void* buffer, std::size_t count) {
	if(!file) {
		return 0;
	}

	std::size_t remainingSize = getSizeReadable();
	if(count > remainingSize) {
		count = remainingSize;
	}

	if(count > 0) {
		file->read(static_cast<char*>(buffer), count);
	}

	return count;
}

std::size_t ReaderFile::getSizeReadable() const {
	if(!file) {
		return 0;
	}

	return getSize() - pos;
}

bool ReaderFile::hasSize() const {
	return file ? true : false;
//	return (bool) file;
}

std::size_t ReaderFile::getSize() const {
	return size;
}

} /* namespace io */
} /* namespace esl */
