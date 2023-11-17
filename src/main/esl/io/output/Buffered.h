#ifndef ESL_IO_OUTPUT_BUFFERED_H_
#define ESL_IO_OUTPUT_BUFFERED_H_

#include <esl/io/Output.h>
#include <esl/io/Reader.h>

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace output {

class Buffered : public Reader {
public:
	static Output create(Reader& baseReader);

	Buffered(Reader& baseReader);

	std::size_t read(void* data, std::size_t size) override;
	std::size_t getSizeReadable() const override;
	bool hasSize() const override;
	std::size_t getSize() const override;

	void setBaseReader(Reader& baseReader);

	void reset();

private:
	static constexpr std::size_t prefetchSize = 4096;

	using CacheLine = std::vector<std::uint8_t>;

	std::reference_wrapper<Reader> baseReader;

	bool completed = false;
	std::size_t currentIndex = npos;
	std::size_t currentPos = 0;

	std::vector<std::unique_ptr<CacheLine>> buffers;
};

} /* namespace output */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_IO_OUTPUT_BUFFERED_H_ */
