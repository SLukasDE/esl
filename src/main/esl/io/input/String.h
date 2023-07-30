/*
MIT License
Copyright (c) 2019-2023 Sven Lukas

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

#ifndef ESL_IO_INPUT_STRING_H_
#define ESL_IO_INPUT_STRING_H_

#include <esl/io/Writer.h>

namespace esl {
inline namespace v1_6 {
namespace io {
namespace input {

class String : public Writer {
public:
	// if function is called with size=0, this signals that writing is done, so write will not be called anymore.
	// -> this can be used for cleanup stuff.
	// returns consumed bytes.
	// npos is returned if writer will not consume anymore.
	std::size_t write(const void* data, std::size_t size) override;

	// returns consumable bytes to write.
	// npos is returned if available size is unknown.
	std::size_t getSizeWritable() const override;

	virtual void process();

	const std::string& getString() const noexcept;

private:
	bool done = false;
	std::string str;
};

} /* namespace input */
} /* namespace io */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_IO_INPUT_STRING_H_ */
