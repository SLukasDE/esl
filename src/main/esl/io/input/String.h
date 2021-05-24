#ifndef ESL_IO_INPUT_STRING_H_
#define ESL_IO_INPUT_STRING_H_

#include <esl/io/Consumer.h>

namespace esl {
namespace io {
namespace input {

class String : public Consumer {
public:
	bool consume(Reader& reader) override;

	const std::string& getString() const noexcept;

private:
	bool done = false;
	std::string str;
};

} /* namespace input */
} /* namespace io */
} /* namespace esl */

#endif /* ESL_IO_INPUT_STRING_H_ */
