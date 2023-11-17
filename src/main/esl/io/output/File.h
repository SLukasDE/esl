#ifndef ESL_IO_OUTPUT_FILE_H_
#define ESL_IO_OUTPUT_FILE_H_

#include <esl/io/Output.h>
#include <esl/io/Reader.h>

#include <fstream>
#include <memory>
#include <string>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace output {

class File : public Reader {
public:
	static Output create(const std::string& filename);

	File(const std::string& filename);

	std::size_t read(void* data, std::size_t size) override;
	std::size_t getSizeReadable() const override;
	bool hasSize() const override;
	std::size_t getSize() const override;

private:
	std::unique_ptr<std::ifstream> file;
	std::size_t size = 0;

	std::size_t pos = 0;
};

} /* namespace output */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_IO_OUTPUT_FILE_H_ */
