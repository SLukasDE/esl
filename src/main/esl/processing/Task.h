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

#ifndef ESL_PROCESSING_TASK_H_
#define ESL_PROCESSING_TASK_H_

#include <esl/object/Object.h>
#include <esl/object/Context.h>
#include <esl/processing/Status.h>

#include <chrono>
#include <exception>
#include <memory>

namespace esl {
namespace processing {

#ifdef ESL_1_6
class Task : public object::Object {
public:
	enum class Status {
		waiting,
		canceled,
		running,
		exception,
		done
	};

	//virtual void onEvent(const object::Object& object) = 0;
	virtual void cancel() = 0;

	virtual Status getStatus() const = 0;
	virtual object::Context* getContext() const = 0;
	virtual std::exception_ptr getException() const = 0;
};
#else
class Task {
public:
	class Binding {
	public:
		virtual ~Binding() = default;

		virtual void sendEvent(const object::Object& object) = 0;
		virtual void cancel() = 0;

		virtual Status getStatus() const = 0;
		virtual object::Context* getContext() const = 0;
		virtual std::exception_ptr getException() const = 0;
	};

	Task(std::shared_ptr<Binding> binding);

	void sendEvent(const object::Object& object);
	void cancel();

	Status getStatus() const;
	object::Context* getContext() const;
	std::exception_ptr getException() const;

private:
	std::shared_ptr<Binding> binding;
};
#endif
} /* namespace processing */
} /* namespace esl */

#endif /* ESL_PROCESSING_TASK_H_ */
