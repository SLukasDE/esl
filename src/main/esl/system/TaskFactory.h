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

#ifndef ESL_SYSTEM_TASKFACTORY_H_
#define ESL_SYSTEM_TASKFACTORY_H_

#include <esl/object/Object.h>
#include <esl/system/Task.h>

#include <vector>

namespace esl {
inline namespace v1_6 {
namespace system {

class TaskFactory : public object::Object {
public:
#ifdef ESL_1_6
	virtual std::shared_ptr<Task> createTask(std::unique_ptr<Procedure> procedure, std::function<void(Status)> onStateChanged, unsigned int priority = 0, std::unique_ptr<object::Context> context = nullptr) = 0;
	virtual std::vector<std::shared_ptr<Task>> getTasks() const = 0;
#else
	virtual Task createTask(Task::Descriptor descriptor) = 0;
	virtual std::vector<Task> getTasks() const = 0;
#endif
};

} /* namespace system */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_SYSTEM_TASKFACTORY_H_ */
