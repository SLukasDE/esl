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

#include <esl/system/Transceiver.h>

#include <memory>

namespace esl {
inline namespace v1_6 {
namespace system {

void Transceiver::operator>>(io::Input&& aInput) {
	input = std::move(aInput);
	inputPath = "";
}

void Transceiver::operator>>(const std::string& path) {
	input = io::Input();
	inputPath = path;
}

void Transceiver::operator<<(io::Output&& aOutput) {
	output = std::move(aOutput);
	outputPath = "";
}

void Transceiver::operator<<(const std::string& path) {
	output = io::Output();
	outputPath = path;
}

const io::Input& Transceiver::getInput() const noexcept {
	return input;
}

const std::string& Transceiver::getInputPath() const noexcept {
	return inputPath;
}

const io::Output& Transceiver::getOutput() const noexcept {
	return output;
}

const std::string& Transceiver::getOutputPath() const noexcept {
	return outputPath;
}

} /* namespace system */
} /* inline namespace v1_6 */
} /* namespace esl */
