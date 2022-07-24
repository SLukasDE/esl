/*
MIT License
Copyright (c) 2019-2022 Sven Lukas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef ESL_IO_FILEPOSITION_H_
#define ESL_IO_FILEPOSITION_H_

#include <memory>
#include <string>

namespace esl {
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
} /* namespace esl */

#endif /* ESL_IO_FILEPOSITION_H_ */
