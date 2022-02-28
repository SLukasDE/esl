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

#ifndef ESL_STACKTRACE_H_
#define ESL_STACKTRACE_H_

#ifndef BOOST_STACKTRACE_USE_ADDR2LINE
#define BOOST_STACKTRACE_USE_ADDR2LINE
#endif

#include <esl/stacktrace/Interface.h>
#include <esl/logging/Location.h>
#include <esl/logging/StreamReal.h>
#include <esl/logging/StreamEmpty.h>
#include <esl/module/Implementation.h>

#include <ostream>
#include <memory>

namespace esl {

class Stacktrace {
public:
	static module::Implementation& getDefault();

	Stacktrace(const stacktrace::Interface::Settings& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());

	Stacktrace(const Stacktrace&);

	void dump(std::ostream& stream) const;
	void dump(logging::StreamReal& stream, logging::Location location = logging::Location{}) const;
	inline void dump(logging::StreamEmpty& stream, logging::Location location = logging::Location{}) const { };

private:
	std::unique_ptr<stacktrace::Interface::Stacktrace> stacktrace;
};

template <class T>
class
StacktraceInjector: public T /*, public std::exception */ {
public:
    explicit StacktraceInjector(T const & x, const Stacktrace& aStacktrace)
    : T(x),
	  stacktrace(aStacktrace)
    { }

    ~StacktraceInjector()
    { }

    static inline const Stacktrace* getStacktrace(const T& t) {
    	const StacktraceInjector* stacktraceInjector = dynamic_cast<const StacktraceInjector *>(&t);
        if(stacktraceInjector) {
            return &stacktraceInjector->stacktrace;
        }
        else {
            return nullptr;
        }
    }

private:
    Stacktrace stacktrace;
};

template <class E>
StacktraceInjector<E> addStacktrace(const E& e) {
    return StacktraceInjector<E>(e, Stacktrace());
}

template <class E>
const Stacktrace* getStacktrace(const E& e) {
	return StacktraceInjector<E>::getStacktrace(e);
}

template<typename F, typename... Args>
auto callStacktrace(F f, Args... args) -> decltype(f(args...)) {
	try {
		return f(args...);
    }
	catch (std::exception& e) {
		if(getStacktrace(e)) {
			throw;
		}
		throw addStacktrace(e);
    }
    catch (...) {
        throw;
    }
}

} /* namespace esl */

#endif /* ESL_STACKTRACE_H_ */
