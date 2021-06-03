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

#include <esl/io/output/String.h>
#include <esl/logging/Logger.h>

namespace esl {
namespace io {
namespace output {

namespace {
esl::logging::Logger<> logger("esl::io::ProducerString");
}

esl::io::Output String::create(std::string content) {
	return esl::io::Output(std::unique_ptr<Producer>(new String(std::move(content))));
}

String::String(std::string aContent)
: data(std::move(aContent)),
  bufferRead(data.data()),
  currentSize(data.size() == 0 ? Writer::npos : data.size())
{ }

std::size_t String::produce(Writer& writer) {
	if(currentPos >= currentSize) {
		currentSize = Writer::npos;
	}

	if(currentSize == Writer::npos) {
		return Writer::npos;
	}

	std::size_t count = writer.write(&bufferRead[currentPos], currentSize - currentPos);
	if(count == Writer::npos) {
		currentPos = currentSize;
	}
	else {
		if(count > currentSize - currentPos) {
			logger.warn << "ProducerString has been called with a broken writer!\n";
			logger.warn << "Writer read " << count << " bytes but at most " << (currentSize - currentPos) << " bytes was allowed to read.\n";
			count = currentSize - currentPos;
		}
		currentPos += count;
	}

	return count;
}

} /* namespace output */
} /* namespace io */
} /* namespace esl */
