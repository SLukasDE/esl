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

#ifndef ESL_IO_INPUT_H_
#define ESL_IO_INPUT_H_

#include <esl/io/Consumer.h>
#include <esl/io/Writer.h>
#include <esl/object/Interface.h>

#include <memory>

namespace esl {
namespace io {

class Input final {
public:
	Input() = default;

	Input(std::unique_ptr<object::Interface::Object> object, Consumer& consumer, Writer& writer);

	Input(Consumer& consumer);
	Input(Writer& writer);

	Input(std::unique_ptr<Consumer> consumerGenerated);
	Input(std::unique_ptr<Writer> writerGenerated);

	Input(const Input&) = delete;
	Input(Input&& other);

	Input& operator=(const Input&) = delete;
	Input& operator=(Input&& other);

	explicit operator bool() const noexcept;

	Consumer& getConsumer() const;
	Writer& getWriter() const;

private:
	std::unique_ptr<object::Interface::Object> object;
	std::unique_ptr<Consumer> consumerGenerated;
	std::unique_ptr<Writer> writerGenerated;

	Consumer* consumer = nullptr;
	Writer* writer = nullptr;
};

} /* namespace io */
} /* namespace esl */

#endif /* ESL_IO_INPUT_H_ */
