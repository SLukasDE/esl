/*
MIT License
Copyright (c) 2019 Sven Lukas

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
#include <esl/logging/Logger.h>
#include <esl/logging/Level.h>
#include <boost/exception/all.hpp>
#include <ostream>
#include <memory>

namespace esl {

class Stacktrace {
//	static logging::Logger logger;
public:
	Stacktrace();
	Stacktrace(const esl::Stacktrace&);
	~Stacktrace() = default;

	static void allowDummy();

	void dump(std::ostream& oStream) const;
//	void dump(logging::Level level = logging::Level::ERROR) const;
	void dump(logging::Logger& logger, logging::Level level = logging::Level::ERROR) const;

private:
	std::unique_ptr<stacktrace::Interface::Stacktrace> stacktrace;
};

typedef boost::error_info<esl::Stacktrace, esl::Stacktrace> StacktraceType;

template <class E>
auto addStacktrace(const E& e) -> decltype(boost::enable_error_info(e)) {
    return boost::enable_error_info(e) << esl::StacktraceType(esl::Stacktrace());
}
/*
template <class E>
auto getStacktrace(const E& e) -> decltype(boost::get_error_info<esl::StacktraceType>(const_cast<E&>(e))) {
	return boost::get_error_info<esl::StacktraceType>(const_cast<E&>(e));
}
*/
template <class E>
esl::Stacktrace* getStacktrace(const E& e) {
	return boost::get_error_info<esl::StacktraceType>(const_cast<E&>(e));
}

template<typename F, typename... Args>
auto callStacktrace(F f, Args... args) -> decltype(f(args...)) {
	try {
		return f(args...);
    }
	catch (std::exception& e) {
		throw esl::addStacktrace(e);
    }
    catch (...) {
        throw;
    }
}

} /* namespace esl */

#endif /* ESL_STACKTRACE_H_ */
