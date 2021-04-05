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

#include <esl/io/Standard.h>

#include <cstdio>

namespace esl {
namespace io {

namespace {
class WriterStandard : public Writer {
public:
	WriterStandard(bool aIsErrStream)
	: stream(aIsErrStream ? stderr : stdout),
	  isErrStream(aIsErrStream)
	{ }

	std::size_t write(const void* data, std::size_t size) override {
		std::size_t rv = std::fwrite(data, size, 1, stream);
		return rv == EOF ? Writer::npos : rv;
	}

	std::size_t getSizeWritable() const {
		return Writer::npos;
	}

	bool isErr() const noexcept {
		return isErrStream;
	}

private:
	FILE* stream;
	bool isErrStream;
};

class ReaderStandard : public Reader {
public:
	ReaderStandard(FILE* aStream)
	: stream(aStream)
	{ }

	std::size_t read(void* data, std::size_t size) override {
		std::size_t rv = std::fread(data, size, 1, stream);
		return rv == EOF ? Reader::npos : rv;
	}

	std::size_t getSizeReadable() const {
		return Reader::npos;
	}

	bool hasSize() const override {
		return false;
	}

	std::size_t getSize() const {
		return Reader::npos;
	}

private:
	FILE* stream;
};

}

Writer& Standard::getOut() {
	static WriterStandard out(false);
	return out;
}

Writer& Standard::getErr() {
	static WriterStandard err(true);
	return err;
}

Reader& Standard::getIn() {
	static ReaderStandard in(stdin);
	return in;
}

bool Standard::isOut(Writer& writer) {
	if(&writer == &getOut()) {
		return true;
	}

	WriterStandard* writerPtr = dynamic_cast<WriterStandard*>(&writer);
	if(writerPtr) {
		return !writerPtr->isErr();
	}

	return false;
}

bool Standard::isErr(Writer& writer) {
	if(&writer == &getErr()) {
		return true;
	}

	WriterStandard* writerPtr = dynamic_cast<WriterStandard*>(&writer);
	if(writerPtr) {
		return writerPtr->isErr();
	}

	return false;
}

bool Standard::isIn(Reader& reader) {
	if(&reader == &getIn()) {
		return true;
	}

	return dynamic_cast<ReaderStandard*>(&reader) != nullptr;
}

} /* namespace io */
} /* namespace esl */
