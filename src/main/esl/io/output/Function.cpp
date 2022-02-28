/*
MIT License
Copyright (c) 2019-2022 Sven Lukas

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

#include <esl/io/output/Function.h>

#include <cstring>

namespace esl {
namespace io {
namespace output {

constexpr std::size_t Function::prefetchSize;

io::Output Function::create(std::function<std::size_t(void*, std::size_t)> getDataFunction) {
	return io::Output(std::unique_ptr<Reader>(new Function(getDataFunction)));
}

Function::Function(std::function<std::size_t(void*, std::size_t)> aGetDataFunction)
: getDataFunction(aGetDataFunction)
{ }

std::size_t Function::read(void* buffer, std::size_t count) {
	std::size_t remainingSize = data.size() - dataPos;

	if(remainingSize == 0 && getDataFunction) {
		std::size_t fetchedSize = getDataFunction(buffer, count);
		if(fetchedSize != Reader::npos) {
			fetchedDirectSize += fetchedSize;
			return fetchedSize;
		}
		getDataFunction = nullptr;
	}

	if(getDataFunction == nullptr) {
		return Reader::npos;
	}

	if(count > remainingSize) {
		count = remainingSize;
	}
	std::memcpy(buffer, &data.data()[dataPos], count);
	dataPos += count;

	return count;
}

std::size_t Function::getSizeReadable() const {
	std::size_t remainingSize = data.size() - dataPos;

	if(remainingSize == 0 && getDataFunction) {
		return Reader::npos;
	}

	return remainingSize;
}

bool Function::hasSize() const {
	/* as long getDataFunction is not nullptr, there
	 * are more data to fetch and a final size is
	 * currently not available */
	return !(getDataFunction);
}

std::size_t Function::getSize() const {
	if(!getDataFunction) {
		return data.size();
	}

	while(prefetchData() > 0) { }
	return data.size() + fetchedDirectSize;
}

std::size_t Function::prefetchData() const {
	char buffer[prefetchSize];

	if(getDataFunction) {
		std::size_t fetchedSize = getDataFunction(buffer, prefetchSize);

		if(fetchedSize != Reader::npos) {
			data.append(buffer, fetchedSize);
			return fetchedSize;
		}

		getDataFunction = nullptr;
	}

	return 0;
}

} /* namespace output */
} /* namespace io */
} /* namespace esl */
