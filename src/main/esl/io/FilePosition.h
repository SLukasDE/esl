/*
 * This file is part of ESL.
 * Copyright (C) 2020-2023 Sven Lukas
 *
 * ESL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ESL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License
 * along with ESL.  If not, see <https://www.gnu.org/licenses/>.
 */

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
	public:
		Injector(Injector const& e)
		: E(e),
		  filePosition(e.filePosition ? new FilePosition(filePosition->getFileName(), filePosition->getLineNo()) : nullptr)
		{ }

		Injector& operator=(Injector const& e)
		{
			static_cast<E&>(*this) = e;
			if(e.filePosition) {
				filePosition.reset(new FilePosition(e.filePosition->getFileName(), e.filePosition->getLineNo()));
			}
		}

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
