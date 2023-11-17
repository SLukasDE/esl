#include <esl/io/input/Closed.h>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace input {

namespace {
Closed closed;
}

esl::io::Input Closed::create() {
	return esl::io::Input(closed);
}

std::size_t Closed::write(const void* data, std::size_t size) {
	return npos;
}

std::size_t Closed::getSizeWritable() const {
	return 0;
}

} /* namespace input */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */
