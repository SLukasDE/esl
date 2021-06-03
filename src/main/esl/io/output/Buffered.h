/*
MIT License
Copyright (c) 2019-2021 Sven Lukas

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

#ifndef ESL_IO_OUTPUT_BUFFERED_H_
#define ESL_IO_OUTPUT_BUFFERED_H_

#include <esl/io/Output.h>
#include <esl/io/Reader.h>

#include <cstdint>
#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace esl {
namespace io {
namespace output {

class Buffered : public Reader {
public:
	static esl::io::Output create(Reader& baseReader);

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
} /* namespace esl */

#endif /* ESL_IO_OUTPUT_BUFFERED_H_ */
