#ifndef ESL_IO_OUTPUT_FUNCTION_H_
#define ESL_IO_OUTPUT_FUNCTION_H_

#include <esl/io/Output.h>
#include <esl/io/Reader.h>

#include <functional>
#include <string>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace output {

class Function : public Reader {
public:
	static Output create(std::function<std::size_t(void*, std::size_t)> getDataFunction);

	Function(std::function<std::size_t(void*, std::size_t)> getDataFunction);

	std::size_t read(void* data, std::size_t size) override;
	std::size_t getSizeReadable() const override;
	bool hasSize() const override;
	std::size_t getSize() const override;

private:
	static constexpr std::size_t prefetchSize = 1024;
	std::size_t prefetchData() const;

	mutable std::function<std::size_t(void*, std::size_t)> getDataFunction;
	mutable std::size_t fetchedDirectSize = 0;

	mutable std::string data;
	std::size_t dataPos = 0;
};

} /* namespace output */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_IO_OUTPUT_FUNCTION_H_ */
