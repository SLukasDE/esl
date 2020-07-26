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

#include <esl/http/client/RequestStatic.h>
#include <esl/http/client/Connection.h>

#include <string.h>

namespace esl {
namespace http {
namespace client {

RequestStatic::RequestStatic(std::string path, utility::HttpMethod method, utility::MIME contentType, const char* aData, std::size_t aSize)
: Request(std::move(path), std::move(method), std::move(contentType)),
  data(aData),
  size(aSize)
{ }

/*
std::size_t RequestStatic::getData(char* buffer, std::size_t count) {
	std::size_t remainingSize = size - dataPos;

	if(count > remainingSize) {
		count = remainingSize;
	}
	std::memcpy(buffer, &data[dataPos], count);
	dataPos += count;

	return count;
}
*/
const char* RequestStatic::getData() const {
	return data;
}

std::size_t RequestStatic::getSize() const {
	return size;
}

} /* namespace client */
} /* namespace http */
} /* namespace esl */
