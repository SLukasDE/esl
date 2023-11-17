#include <esl/io/input/String.h>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace input {

std::size_t String::write(const void* data, std::size_t size) {
	if(done) {
		return npos;
	}

	if(size > 0) {
		str += std::string(static_cast<const char*>(data), size);
		return size;
	}

	done = true;
	process();
	return npos;
}

std::size_t String::getSizeWritable() const {
	return npos;
}

void String::process() {
}

const std::string& String::getString() const noexcept {
	return str;
}

} /* namespace input */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */
