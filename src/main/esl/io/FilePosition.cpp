#include <esl/io/FilePosition.h>

namespace esl {
inline namespace v1_6 {
namespace io {

FilePosition::FilePosition(const std::string& aFileName, int aLineNo)
: fileName(aFileName),
  lineNo(aLineNo)
{ }

const std::string& FilePosition::getFileName() const noexcept {
	return fileName;
}

const int FilePosition::getLineNo() const noexcept {
	return lineNo;
}

} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */
