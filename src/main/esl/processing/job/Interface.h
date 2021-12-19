/*
MIT License
Copyright (c) 2019-2021 Sven Lukas

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

#ifndef ESL_PROCESSING_JOB_INTERFACE_H_
#define ESL_PROCESSING_JOB_INTERFACE_H_

#include <esl/processing/job/Context.h>
#include <esl/processing/job/Handle.h>
#include <esl/processing/job/Job.h>
#include <esl/module/Interface.h>
#include <esl/object/Interface.h>

#include <memory>

namespace esl {
namespace processing {
namespace job {

struct Interface : esl::module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class Runner { // : public object::Interface::Object {
	public:
		virtual ~Runner() = default;

		virtual Handle addJob(std::unique_ptr<Job> job) = 0;
		virtual void cancel(Handle jobId) = 0;
	};

	using CreateRunner = std::unique_ptr<Runner> (*)(const Settings& settings);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-job";
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static std::unique_ptr<const esl::module::Interface> createInterface(const char* implementation, CreateRunner createRunner) {
		return std::unique_ptr<const esl::module::Interface>(new Interface(implementation, createRunner));
	}

	Interface(const char* implementation, CreateRunner aCreateRunner)
	: esl::module::Interface(esl::getModule().getId(), getType(), implementation, esl::getModule().getApiVersion()),
	  createRunner(aCreateRunner)
	{ }

	CreateRunner createRunner;
};

} /* namespace job */
} /* namespace processing */
} /* namespace esl */

#endif /* ESL_PROCESSING_JOB_INTERFACE_H_ */
