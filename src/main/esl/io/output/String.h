#ifndef ESL_IO_OUTPUT_STRING_H_
#define ESL_IO_OUTPUT_STRING_H_

#include <esl/io/Output.h>
#include <esl/io/Producer.h>
#include <esl/io/Writer.h>

#include <string>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace output {

class String : public esl::io::Producer {
public:
	static esl::io::Output create(std::string content);

	String(std::string content);

	std::size_t produce(esl::io::Writer& writer) override;

private:
	std::string str;

	const char* data;
	std::size_t size = 0;
	std::size_t currentPos = 0;
};

} /* namespace output */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_IO_OUTPUT_STRING_H_ */
