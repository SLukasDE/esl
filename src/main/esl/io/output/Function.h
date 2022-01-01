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

#ifndef ESL_IO_OUTPUT_FUNCTION_H_
#define ESL_IO_OUTPUT_FUNCTION_H_

#include <esl/io/Output.h>
#include <esl/io/Reader.h>

#include <string>
#include <functional>

namespace esl {
namespace io {
namespace output {

class Function : public Reader {
public:
	static esl::io::Output create(std::function<std::size_t(void*, std::size_t)> getDataFunction);

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
} /* namespace esl */

#endif /* ESL_IO_OUTPUT_FUNCTION_H_ */
