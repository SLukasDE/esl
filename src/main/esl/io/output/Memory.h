#ifndef ESL_IO_OUTPUT_MEMORY_H_
#define ESL_IO_OUTPUT_MEMORY_H_

#include <esl/io/Output.h>
#include <esl/io/Producer.h>
#include <esl/io/Writer.h>

#include <string>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace output {

class Memory : public Producer {
public:
	static Output create(const void* data, std::size_t size);

	Memory(const void* data, std::size_t size);

	std::size_t produce(esl::io::Writer& writer) override;

	const void* getData() const noexcept;
	std::size_t getSize() const noexcept;

private:
	const void* data;
	std::size_t size;
	std::size_t currentPos = 0;
};

} /* namespace output */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_IO_OUTPUT_MEMORY_H_ */
