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

#include <esl/system/FileDescriptor.h>

namespace esl {
namespace system {

namespace {
constexpr int stdInHandle = 0;
constexpr int stdOutHandle = 1;
constexpr int stdErrHandle = 2;
}

FileDescriptor::FileDescriptor(int aId)
: id(aId)
{ }

int FileDescriptor::getId() const noexcept {
	return id;
}

FileDescriptor& FileDescriptor::getOut() {
	static FileDescriptor out(stdOutHandle);
	return out;
}

FileDescriptor& FileDescriptor::getErr() {
	static FileDescriptor err(stdErrHandle);
	return err;
}

FileDescriptor& FileDescriptor::getIn() {
	static FileDescriptor in(stdInHandle);
	return in;
}

bool FileDescriptor::isOut(const FileDescriptor& fileDescriptor) noexcept {
	if(&fileDescriptor == &getOut()) {
		return true;
	}

	return fileDescriptor.getId() == getOut().getId();
}

bool FileDescriptor::isErr(const FileDescriptor& fileDescriptor) noexcept {
	if(&fileDescriptor == &getErr()) {
		return true;
	}

	return fileDescriptor.getId() == getErr().getId();
}

bool FileDescriptor::isIn(const FileDescriptor& fileDescriptor) noexcept {
	if(&fileDescriptor == &getIn()) {
		return true;
	}

	return fileDescriptor.getId() == getIn().getId();
}

} /* namespace system */
} /* namespace esl */
