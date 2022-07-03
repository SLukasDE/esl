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

#ifndef ESL_PROCESSING_TASKDESCRIPTOR_H_
#define ESL_PROCESSING_TASKDESCRIPTOR_H_

#include <esl/object/Context.h>
#include <esl/processing/Procedure.h>
#include <esl/processing/Status.h>

#include <functional>
#include <memory>

namespace esl {
namespace processing {

struct TaskDescriptor {
public:
	std::unique_ptr<Procedure> procedure;
	std::unique_ptr<object::Context> context;
	unsigned int priority = 0;
	std::function<void(Status)> onStateChanged;
};

} /* namespace processing */
} /* namespace esl */

#endif /* ESL_PROCESSING_TASKDESCRIPTOR_H_ */
