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

#ifndef ESL_PROCESSING_TASK_INTERFACE_H_
#define ESL_PROCESSING_TASK_INTERFACE_H_

#include <esl/processing/procedure/Interface.h>
#include <esl/module/Interface.h>
#include <esl/object/Interface.h>
#include <esl/object/ObjectContext.h>
#include <esl/object/Event.h>

#include <chrono>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace esl {
namespace processing {
namespace task {

struct Interface : esl::module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class Task : public object::Interface::Object {
	public:
		using Handle = int;
		enum class Status {
			waiting,
			running,
			done
		};

		virtual Handle runTask(std::unique_ptr<procedure::Interface::Procedure> procedure, std::unique_ptr<object::ObjectContext> objectContext) = 0;
		virtual Handle runTask(procedure::Interface::Procedure& procedure, std::unique_ptr<object::ObjectContext> objectContext) = 0;
		virtual std::unique_ptr<object::ObjectContext> cancelTask(const Handle& taskId) = 0;

		virtual Status getTaskStatus(const Handle& taskId) const = 0;
		virtual std::vector<Handle> getTaskHandles() const = 0;

		virtual void sendEvent(const Handle& taskId, const object::Interface::Object& object) const = 0;

		virtual std::set<Handle> waitForTaskStatus(const std::set<Handle>& taskIds, const std::set<Status>& status) const = 0;
		virtual std::set<Handle> waitForTaskStatus(const std::set<Handle>& taskIds, const std::set<Status>& status, std::chrono::milliseconds timeout) const = 0;

		virtual std::unique_ptr<object::ObjectContext> waitForTaskDone(Handle taskId) = 0;
		virtual std::unique_ptr<object::ObjectContext> waitForTaskDone(Handle taskId, std::chrono::milliseconds timeout) = 0;
	};

	using CreateTask = std::unique_ptr<Task> (*)(const std::vector<std::pair<std::string, std::string>>& settings);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-processing-task";
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static std::unique_ptr<const esl::module::Interface> createInterface(const char* implementation, CreateTask createTask) {
		return std::unique_ptr<const esl::module::Interface>(new Interface(implementation, createTask));
	}

	Interface(const char* implementation, CreateTask aCreateTask)
	: esl::module::Interface(esl::getModule().getId(), getType(), implementation, esl::getModule().getApiVersion()),
	  createTask(aCreateTask)
	{ }

	CreateTask createTask;
};

} /* namespace task */
} /* namespace processing */
} /* namespace esl */

#endif /* ESL_PROCESSING_TASK_INTERFACE_H_ */
