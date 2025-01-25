/*
MIT License
Copyright (c) 2019-2025 Sven Lukas

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

#ifndef ESL_SYSTEM_TRANSCEIVER_H_
#define ESL_SYSTEM_TRANSCEIVER_H_

#include <esl/io/Input.h>
#include <esl/io/Output.h>

#include <string>

namespace esl {
inline namespace v1_6 {
namespace system {

class Transceiver {
public:
	Transceiver() = default;
	Transceiver(const Transceiver&) = delete;
	Transceiver(Transceiver&&) = delete;

	Transceiver& operator=(const Transceiver&) = delete;
	Transceiver& operator=(Transceiver&& other) = delete;

	void operator>>(io::Input&& input);
	void operator>>(const std::string& path);

	void operator<<(io::Output&& output);
	void operator<<(const std::string& path);

	const io::Input& getInput() const noexcept;
	const std::string& getInputPath() const noexcept;

	const io::Output& getOutput() const noexcept;
	const std::string& getOutputPath() const noexcept;

private:
	io::Input input;
	std::string inputPath;

	io::Output output;
	std::string outputPath;
};

} /* namespace system */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_SYSTEM_TRANSCEIVER_H_ */
