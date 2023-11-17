#include <esl/io/output/Memory.h>
#include <esl/Logger.h>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace output {

namespace {
Logger logger("esl::io::output::Memory");
}

esl::io::Output Memory::create(const void* data, std::size_t size) {
    return esl::io::Output(std::unique_ptr<esl::io::Producer>(new Memory(data, size)));
}

Memory::Memory(const void* aData, std::size_t aSize)
: data(aData),
  size(aSize)
{ }

std::size_t Memory::produce(esl::io::Writer& writer) {
	if(currentPos >= size) {
		size = esl::io::Writer::npos;
	}

	if(size == esl::io::Writer::npos) {
		return esl::io::Writer::npos;
	}

	std::size_t count = writer.write(&static_cast<const char*>(getData())[currentPos], size - currentPos);
	//std::size_t count = writer.write(static_cast<const char*>(getData()) + currentPos, size - currentPos);
	if(count == esl::io::Writer::npos) {
		currentPos = size;
	}
	else {
		if(count > size - currentPos) {
			logger.warn << "output::Memory has been called with a broken writer!\n";
			logger.warn << "Writer read " << count << " bytes but at most " << (size - currentPos) << " bytes was allowed to read.\n";
			count = size - currentPos;
		}
		currentPos += count;
	}

	return count;
}

const void* Memory::getData() const noexcept {
	return data;
}

std::size_t Memory::getSize() const noexcept {
	return size;
}

} /* namespace output */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */
