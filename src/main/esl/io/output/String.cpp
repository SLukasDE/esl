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
: str(std::move(aContent)),
  data(str.data()),
  size(str.size() == 0 ? Writer::npos : str.size())
{ }

std::size_t String::produce(Writer& writer) {
	if(currentPos >= size) {
		size = Writer::npos;
		return Writer::npos;
	}

	if(size == Writer::npos) {
		return Writer::npos;
	}

	std::size_t count = writer.write(&data[currentPos], size - currentPos);
	if(count == Writer::npos) {
		currentPos = size;
	}
	else {
		if(currentPos + count > size) {
			logger.warn << "output::String has been called with a broken writer!\n";
			logger.warn << "Writer read " << count << " bytes but at most " << (size - currentPos) << " bytes was allowed to read.\n";
			count = size - currentPos;
		}
		currentPos += count;
	}

	return count;
}

} /* namespace output */
} /* namespace io */
} /* namespace esl */
