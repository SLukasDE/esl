#ifndef ESL_IO_FILEPOSITION_H_
#define ESL_IO_FILEPOSITION_H_

#include <memory>
#include <string>

namespace esl {
inline namespace v1_6 {
namespace io {

class FilePosition {
public:
	template <class E>
	class Injector : public E {
	friend class FilePosition;
	private:
	    Injector(E const & e, std::unique_ptr<FilePosition> aFilePosition)
	    : E(e),
		  filePosition(std::move(aFilePosition))
	    { }

		std::unique_ptr<FilePosition> filePosition;
	};

	FilePosition(const std::string& fileName, int lineNo);

	const std::string& getFileName() const noexcept;
	const int getLineNo() const noexcept;

	template <class E>
	static Injector<E> add(const std::string& fileName, int lineNo, const E& e);

	template <class E>
	static const FilePosition* get(const E& e);

private:
	const std::string fileName;
	const int lineNo;
};

template <class E>
FilePosition::Injector<E> FilePosition::add(const std::string& fileName, int lineNo, const E& e) {
	return FilePosition::Injector<E>(e, std::unique_ptr<FilePosition>(new FilePosition(fileName, lineNo)));
}

template <class E>
const FilePosition* FilePosition::get(const E& e) {
	const FilePosition::Injector<E>* injector = dynamic_cast<const FilePosition::Injector<E>*>(&e);
    return injector ? injector->filePosition.get() : nullptr;
}

} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_IO_FILEPOSITION_H_ */
