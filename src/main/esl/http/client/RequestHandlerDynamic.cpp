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

#include <esl/http/client/RequestHandlerDynamic.h>

#include <algorithm>
#include <cstring>

namespace esl {
namespace http {
namespace client {

RequestHandlerDynamic::RequestHandlerDynamic(utility::MIME contentType, std::function<std::size_t(char*, std::size_t)> aGetDataFunction)
: RequestHandler(std::move(contentType)),
  dynamicType(dataFunction),
  getDataFunction(aGetDataFunction)
{ }

RequestHandlerDynamic::RequestHandlerDynamic(utility::MIME contentType, std::string aData)
: RequestHandler(std::move(contentType)),
  dynamicType(dataString),
  data(std::move(aData))
{ }

std::size_t RequestHandlerDynamic::producer(char* buffer, std::size_t count) {
	std::size_t remainingSize = data.size() - dataPos;

	if(remainingSize == 0 && getDataFunction) {
		std::size_t fetchedSize = getDataFunction(buffer, count);
		fetchedDirectSize += fetchedSize;
		return fetchedSize;
	}

	if(count > remainingSize) {
		count = remainingSize;
	}
	std::memcpy(buffer, &data.data()[dataPos], count);
	dataPos += count;

	return count;
}

bool RequestHandlerDynamic::hasSize() const {
	/* as long getDataFunction is not nullptr, there
	 * are more data to fetch and a final size is
	 * currently not available */
	return !(getDataFunction);
}

std::size_t RequestHandlerDynamic::getSize() const {
	if(!getDataFunction) {
		return data.size();
	}

	while(prefetchData(1024) > 0) { }
	return data.size() + fetchedDirectSize;
}

bool RequestHandlerDynamic::isEmpty() const {
	if(getDataFunction && data.empty()) {
		/* prefetch up to 1024 byte if possible */
		prefetchData(1024);
	}

	return data.empty();
}

std::size_t RequestHandlerDynamic::prefetchData(std::size_t count) const {
	std::size_t result = 0;
	char buffer[1024];

	while(getDataFunction && count > 0) {
		std::size_t fetchSize = std::min(count, static_cast<std::size_t>(sizeof(buffer)));
		std::size_t fetchedSize = getDataFunction(buffer, fetchSize);

		data.append(buffer, fetchedSize);
		count -= fetchedSize;

		if(fetchedSize < fetchSize) {
			getDataFunction = nullptr;
		}
	}

	return result;
}

} /* namespace client */
} /* namespace http */
} /* namespace esl */
