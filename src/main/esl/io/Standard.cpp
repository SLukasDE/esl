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
