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

#ifndef ESL_PROCESSING_TASK_TASK_H_
#define ESL_PROCESSING_TASK_TASK_H_

#include <esl/processing/task/Interface.h>
#include <esl/module/Implementation.h>
#include <esl/processing/procedure/Interface.h>
#include <esl/module/Interface.h>
#include <esl/object/Interface.h>
#include <esl/object/ObjectContext.h>

#include <chrono>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace esl {
namespace processing {
namespace task {

class Context;

class Task final : public Interface::Task {
public:
	static module::Implementation& getDefault();

	Task(const std::vector<std::pair<std::string, std::string>>& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());

	Handle runTask(std::unique_ptr<procedure::Interface::Procedure> procedure, std::unique_ptr<object::ObjectContext> objectContext) override;
	Handle runTask(procedure::Interface::Procedure& procedure, std::unique_ptr<object::ObjectContext> objectContext) override;
	std::unique_ptr<object::ObjectContext> cancelTask(const Handle& taskId) override;

	Status getTaskStatus(const Handle& taskId) const override;
	std::vector<Handle> getTaskHandles() const override;
	void sendEvent(const Handle& taskId, const object::Interface::Object& object) const override;

	std::set<Handle> waitForTaskStatus(const std::set<Handle>& taskIds, const std::set<Status>& status) const override;
	std::set<Handle> waitForTaskStatus(const std::set<Handle>& taskIds, const std::set<Status>& status, std::chrono::milliseconds timeout) const override;

	std::unique_ptr<object::ObjectContext> waitForTaskDone(Handle taskId) override;
	std::unique_ptr<object::ObjectContext> waitForTaskDone(Handle taskId, std::chrono::milliseconds timeout) override;

private:
	std::unique_ptr<Interface::Task> task;
};

} /* namespace task */
} /* namespace processing */
} /* namespace esl */

#endif /* ESL_PROCESSING_TASK_TASK_H_ */
