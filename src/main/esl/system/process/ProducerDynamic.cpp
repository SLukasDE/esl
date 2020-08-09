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

#include <esl/system/process/ProducerDynamic.h>

namespace esl {
namespace system {
namespace process {

ProducerDynamic::ProducerDynamic(std::function<std::size_t(char*, std::size_t)> aGetDataFunction)
: getDataFunction(aGetDataFunction),
  bufferRead(buffer)
{ }

ProducerDynamic::ProducerDynamic(std::string aContent)
: data(std::move(aContent)),
  bufferRead(data.data()),
  currentSize(data.size() == 0 ? utility::Writer::npos : data.size())
{ }

std::size_t ProducerDynamic::write(utility::Writer& writer) {
	if(currentPos >= currentSize) {
		if(getDataFunction) {
			currentPos = 0;
			currentSize = getDataFunction(buffer, sizeof(buffer));

			if(currentSize == 0) {
				currentSize = utility::Writer::npos;
			}
		}
		else {
			currentSize = utility::Writer::npos;
		}
	}

	if(currentSize == utility::Writer::npos) {
		return utility::Writer::npos;
	}

	std::size_t count = writer.write(&bufferRead[currentPos], currentSize - currentPos);
	if(count != utility::Writer::npos) {
		currentPos += count;
	}

	return count;
}
/*
std::size_t ProducerDynamic::write(Interface::FileDescriptor& fileDescriptor) {
	if(currentPos >= currentSize) {
		if(getDataFunction) {
			currentPos = 0;
			currentSize = getDataFunction(buffer, sizeof(buffer));

			if(currentSize == 0) {
				currentSize = Interface::FileDescriptor::npos;
			}
		}
		else {
			currentSize = Interface::FileDescriptor::npos;
		}
	}

	if(currentSize == Interface::FileDescriptor::npos) {
		return Interface::FileDescriptor::npos;
	}

	std::size_t count = fileDescriptor.write(&bufferRead[currentPos], currentSize - currentPos);
	if(count != Interface::FileDescriptor::npos) {
		currentPos += count;
	}

	return count;
}
*/
} /* namespace process */
} /* namespace system */
} /* namespace esl */
