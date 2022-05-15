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

#ifndef ESL_PROCESSING_JOB_JOB_H_
#define ESL_PROCESSING_JOB_JOB_H_

#include <esl/processing/job/Interface.h>
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
namespace job {

class Context;

class Job final : public Interface::Job {
public:
	static module::Implementation& getDefault();

	Job(const std::vector<std::pair<std::string, std::string>>& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());

	Handle runJob(std::unique_ptr<procedure::Interface::Procedure> procedure, std::unique_ptr<object::ObjectContext> objectContext) override;
	Handle runJob(procedure::Interface::Procedure& procedure, std::unique_ptr<object::ObjectContext> objectContext) override;
	std::unique_ptr<object::ObjectContext> cancelJob(Handle jobId) override;

	Status getJobStatus(Handle jobId) const override;
	std::vector<Handle> getJobHandles() const override;
	void sendEvent(const object::Interface::Object& object) const override;

	std::set<Handle> waitForJobStatus(const std::set<Handle>& jobIds, const std::set<Status>& status) const override;
	std::set<Handle> waitForJobStatus(const std::set<Handle>& jobIds, const std::set<Status>& status, std::chrono::milliseconds timeout) const override;

	std::unique_ptr<object::ObjectContext> waitForJobDone(Handle jobId) override;
	std::unique_ptr<object::ObjectContext> waitForJobDone(Handle jobId, std::chrono::milliseconds timeout) override;

private:
	std::unique_ptr<Interface::Job> job;
};

} /* namespace job */
} /* namespace processing */
} /* namespace esl */

#endif /* ESL_PROCESSING_JOB_JOB_H_ */
