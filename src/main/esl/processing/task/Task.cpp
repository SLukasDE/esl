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

#include <esl/processing/task/Task.h>
#include <esl/Module.h>

namespace esl {
namespace processing {
namespace task {

module::Implementation& Task::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

Task::Task(const std::vector<std::pair<std::string, std::string>>& settings, const std::string& implementation)
: task(getModule().getInterface<Interface>(implementation).createTask(settings))
{ }

Task::Handle Task::runTask(std::unique_ptr<procedure::Interface::Procedure> procedure, std::unique_ptr<object::ObjectContext> objectContext) {
	return task->runTask(std::move(procedure), std::move(objectContext));
}

Task::Handle Task::runTask(procedure::Interface::Procedure& procedure, std::unique_ptr<object::ObjectContext> objectContext) {
	return task->runTask(procedure, std::move(objectContext));
}

std::unique_ptr<object::ObjectContext> Task::cancelTask(const Task::Handle& taskId) {
	return task->cancelTask(taskId);
}

Task::Status Task::getTaskStatus(const Task::Handle& taskId) const {
	return task->getTaskStatus(taskId);
}

std::vector<Task::Handle> Task::getTaskHandles() const {
	return task->getTaskHandles();
}

void Task::sendEvent(const Task::Handle& taskId, const object::Interface::Object& object) const {
	task->sendEvent(taskId, object);
}


std::set<Task::Handle> Task::waitForTaskStatus(const std::set<Task::Handle>& taskIds, const std::set<Task::Status>& status) const {
	return task->waitForTaskStatus(taskIds, status);
}

std::set<Task::Handle> Task::waitForTaskStatus(const std::set<Task::Handle>& taskIds, const std::set<Task::Status>& status, std::chrono::milliseconds timeout) const {
	return task->waitForTaskStatus(taskIds, status, timeout);
}


std::unique_ptr<object::ObjectContext> Task::waitForTaskDone(Task::Handle taskId) {
	return task->waitForTaskDone(taskId);
}

std::unique_ptr<object::ObjectContext> Task::waitForTaskDone(Task::Handle taskId, std::chrono::milliseconds timeout) {
	return task->waitForTaskDone(taskId, timeout);
}

} /* namespace task */
} /* namespace processing */
} /* namespace esl */
