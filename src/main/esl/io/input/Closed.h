#ifndef ESL_IO_INPUT_CLOSED_H_
#define ESL_IO_INPUT_CLOSED_H_

#include <esl/io/Writer.h>
#include <esl/io/Input.h>

#include <memory>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace input {

class Closed : public Writer {
public:
	static Input create();

	std::size_t write(const void* data, std::size_t size) override;
	std::size_t getSizeWritable() const override;
};

} /* namespace input */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_IO_INPUT_CLOSED_H_ */
