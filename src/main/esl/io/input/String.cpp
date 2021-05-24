#include <esl/io/input/String.h>

namespace esl {
namespace io {
namespace input {

bool String::consume(Reader& reader) {
	if(done) {
		return false;
	}

	char buffer[1024];
	std::size_t size = reader.read(buffer, 1024);

	if(size == Reader::npos) {
		done = true;
		return false;
	}
	else {
		str.append(buffer, size);
		return true;
	}
}

const std::string& String::getString() const noexcept {
	return str;
}

} /* namespace input */
} /* namespace io */
} /* namespace esl */
