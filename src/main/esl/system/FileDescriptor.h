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

#ifndef ESL_SYSTEM_FILEDESCRIPTOR_H_
#define ESL_SYSTEM_FILEDESCRIPTOR_H_

namespace esl {
namespace system {

class FileDescriptor {
public:
	int getId() const noexcept;

	static FileDescriptor& getOut();
	static FileDescriptor& getErr();
	static FileDescriptor& getIn();

	static bool isOut(const FileDescriptor& fileDescriptor) noexcept;
	static bool isErr(const FileDescriptor& fileDescriptor) noexcept;
	static bool isIn(const FileDescriptor& fileDescriptor) noexcept;

private:
	FileDescriptor(int id);

	int id = -1;
};

} /* namespace system */
} /* namespace esl */

#endif /* ESL_SYSTEM_FILEDESCRIPTOR_H_ */
