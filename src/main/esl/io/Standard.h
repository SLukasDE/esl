#ifndef ESL_IO_STANDARD_H_
#define ESL_IO_STANDARD_H_

#include <esl/io/Reader.h>
#include <esl/io/Writer.h>

namespace esl {
inline namespace v1_6 {
namespace io {

class Standard {
public:
	static Writer& getOut();
	static Writer& getErr();
	static Reader& getIn();

	static bool isOut(const Writer& writer) noexcept;
	static bool isErr(const Writer& writer) noexcept;
	static bool isIn(const Reader& reader) noexcept;

private:
	Standard() = delete;
	~Standard() = delete;
};

} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_IO_STANDARD_H_ */
