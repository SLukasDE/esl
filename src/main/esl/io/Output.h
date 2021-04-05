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

#ifndef ESL_IO_OUTPUT_H_
#define ESL_IO_OUTPUT_H_

#include <esl/io/Producer.h>
#include <esl/io/Reader.h>

#include <memory>

namespace esl {
namespace io {

class Output final {
public:
	Output() = default;
/*
	Output(Producer& producer, Reader& reader);
	Output(Reader& reader, Producer& producer);
*/
	Output(Reader& reader);
	Output(Producer& producer);

	Output(std::unique_ptr<Reader> readerGenerated);
	Output(std::unique_ptr<Producer> producerGenerated);

	Output(const Output&) = delete;
	Output(Output&& other);

	Output& operator=(const Output&) = delete;
	Output& operator=(Output&& other);

	explicit operator bool() const noexcept;

	Producer& getProducer() const noexcept;
	Reader& getReader() const noexcept;

private:
	std::unique_ptr<Producer> producerGenerated;
	std::unique_ptr<Reader> readerGenerated;

	Producer* producer = nullptr;
	Reader* reader = nullptr;
};

} /* namespace io */
} /* namespace esl */

#endif /* ESL_IO_OUTPUT_H_ */
