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

#ifndef ESL_SYSTEM_STACKTRACE_H_
#define ESL_SYSTEM_STACKTRACE_H_

#include <esl/logging/StreamReal.h>
#include <esl/logging/StreamEmpty.h>
#include <esl/logging/Location.h>
#include <esl/plugin/Registry.h>

#include <memory>
#include <ostream>
#include <stdexcept>

namespace esl {
namespace system {

template <class T>
class StacktraceInjector;

class Stacktrace {
public:
	Stacktrace() = default;
	virtual ~Stacktrace() = default;

	virtual void dump(std::ostream& stream) const = 0;
	virtual void dump(logging::StreamReal& stream, logging::Location location = logging::Location{}) const = 0;
	inline void dump(logging::StreamEmpty& stream, logging::Location location = logging::Location{}) const { };

	virtual void dumpFull(std::ostream& stream) const = 0;
	virtual void dumpFull(logging::StreamReal& stream, logging::Location location = logging::Location{}) const = 0;
	inline void dumpFull(logging::StreamEmpty& stream, logging::Location location = logging::Location{}) const { };

	virtual std::unique_ptr<Stacktrace> clone() const = 0;

	template <class E>
	static StacktraceInjector<E> add(const E& e);

	template <class E>
	static const Stacktrace* get(const E& e);

	template<typename F, typename... Args>
	static auto call(F f, Args... args) -> decltype(f(args...)) {
		try {
			return f(args...);
	    }
		catch(const std::exception& e) {
			if(get(e)) {
				throw;
			}
			throw add(e);
	    }
	}
};

template <class T>
class StacktraceInjector : public T {
public:
    StacktraceInjector(T const & x, std::unique_ptr<Stacktrace> aStacktrace)
    : T(x),
	  stacktrace(std::move(aStacktrace))
    { }

    static inline const Stacktrace* getStacktrace(const T& t) {
    	const StacktraceInjector* stacktraceInjector = dynamic_cast<const StacktraceInjector *>(&t);
        if(stacktraceInjector) {
            return stacktraceInjector->stacktrace.get();
        }
        else {
            return nullptr;
        }
    }

private:
	std::unique_ptr<Stacktrace> stacktrace;
};

template <class E>
StacktraceInjector<E> Stacktrace::add(const E& e) {
    return StacktraceInjector<E>(e, plugin::Registry::get().create<Stacktrace>("", {}));

//	const Stacktrace::Plugin* stacktracePlugin = plugin::Registry::get().findPlugin<Stacktrace>("");
//	return StacktraceInjector<E>(e, stacktracePlugin ? stacktracePlugin->create({}) : nullptr);
}

template <class E>
const Stacktrace* Stacktrace::get(const E& e) {
	return StacktraceInjector<E>::getStacktrace(e);
}

} /* namespace system */
} /* namespace esl */

#endif /* ESL_SYSTEM_STACKTRACE_H_ */
