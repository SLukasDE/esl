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

#include <esl/processing/job/Job.h>
#include <esl/Module.h>

namespace esl {
namespace processing {
namespace job {

module::Implementation& Job::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

Job::Job(const std::vector<std::pair<std::string, std::string>>& settings, const std::string& implementation)
: job(getModule().getInterface<Interface>(implementation).createJob(settings))
{ }

Job::Handle Job::runJob(std::unique_ptr<procedure::Interface::Procedure> procedure, std::unique_ptr<object::ObjectContext> objectContext) {
	return job->runJob(std::move(procedure), std::move(objectContext));
}

Job::Handle Job::runJob(procedure::Interface::Procedure& procedure, std::unique_ptr<object::ObjectContext> objectContext) {
	return job->runJob(procedure, std::move(objectContext));
}


std::unique_ptr<object::ObjectContext> Job::cancelJob(Job::Handle jobId) {
	return job->cancelJob(jobId);
}


Job::Status Job::getJobStatus(Job::Handle jobId) const {
	return job->getJobStatus(jobId);
}

std::vector<Job::Handle> Job::getJobHandles() const {
	return job->getJobHandles();
}

void Job::sendEvent(const object::Interface::Object& object) const {
	job->sendEvent(object);
}


std::set<Job::Handle> Job::waitForJobStatus(const std::set<Job::Handle>& jobIds, const std::set<Job::Status>& status) const {
	return job->waitForJobStatus(jobIds, status);
}

std::set<Job::Handle> Job::waitForJobStatus(const std::set<Job::Handle>& jobIds, const std::set<Job::Status>& status, std::chrono::milliseconds timeout) const {
	return job->waitForJobStatus(jobIds, status, timeout);
}


std::unique_ptr<object::ObjectContext> Job::waitForJobDone(Job::Handle jobId) {
	return job->waitForJobDone(jobId);
}

std::unique_ptr<object::ObjectContext> Job::waitForJobDone(Job::Handle jobId, std::chrono::milliseconds timeout) {
	return job->waitForJobDone(jobId, timeout);
}

} /* namespace procedure */
} /* namespace processing */
} /* namespace esl */
