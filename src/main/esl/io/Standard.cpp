/*
 * This file is part of ESL.
 * Copyright (C) 2020-2023 Sven Lukas
 *
 * ESL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ESL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License
 * along with ESL.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <esl/io/Standard.h>

#include <cstdio>

namespace esl {
inline namespace v1_6 {
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

bool Standard::isOut(const Writer& writer) noexcept {
	if(&writer == &getOut()) {
		return true;
	}

	const WriterStandard* writerPtr = dynamic_cast<const WriterStandard*>(&writer);
	if(writerPtr) {
		return !writerPtr->isErr();
	}

	return false;
}

bool Standard::isErr(const Writer& writer) noexcept {
	if(&writer == &getErr()) {
		return true;
	}

	const WriterStandard* writerPtr = dynamic_cast<const WriterStandard*>(&writer);
	if(writerPtr) {
		return writerPtr->isErr();
	}

	return false;
}

bool Standard::isIn(const Reader& reader) noexcept {
	if(&reader == &getIn()) {
		return true;
	}

	return dynamic_cast<const ReaderStandard*>(&reader) != nullptr;
}

} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */
