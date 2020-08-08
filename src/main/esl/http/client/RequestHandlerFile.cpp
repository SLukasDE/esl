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

#include <esl/http/client/RequestHandlerFile.h>

#include <stdexcept>

namespace esl {
namespace http {
namespace client {

RequestHandlerFile::RequestHandlerFile(utility::MIME contentType, std::string aFilename)
: RequestHandler(std::move(contentType)),
  filename(std::move(aFilename))
{ }

std::size_t RequestHandlerFile::producer(char* buffer, std::size_t count) {
	std::ifstream& fileStream = getFileStream();
	if(!fileStream.good()) {
		return 0;
	}

	std::size_t remainingSize = getSize() - pos;
	if(count > remainingSize) {
		count = remainingSize;
	}

	fileStream.read(buffer, count);

	return count;
}

bool RequestHandlerFile::hasSize() const {
	getFileStream();
	return true;
}

std::size_t RequestHandlerFile::getSize() const {
	if(!file) {
		getFileStream();
	}
	return size;
}

bool RequestHandlerFile::isEmpty() const {
	return getSize() == 0;
}

const std::string& RequestHandlerFile::getFilename() const noexcept {
	return filename;
}

std::ifstream& RequestHandlerFile::getFileStream() const {
	if(!file) {

		file = std::unique_ptr<std::ifstream>(new std::ifstream(filename));
		if(!file->good()) {
	        throw std::runtime_error("esl: cannot open file \"" + filename + "\"");
		}

		const auto begin = file->tellg();
		file->seekg(0, std::ios::end);
		const auto end = file->tellg();
		size = (end-begin);
	}
	return *file;
}

} /* namespace client */
} /* namespace http */
} /* namespace esl */
