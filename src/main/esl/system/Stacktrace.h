/*
MIT License
Copyright (c) 2019-2025 Sven Lukas

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

#include <esl/monitoring/Streams.h>
#include <esl/plugin/Registry.h>
#include <esl/system/StacktraceFactory.h>

#include <memory>
#include <ostream>
#include <stdexcept>

namespace esl {
inline namespace v1_6 {
namespace system {

class Stacktrace {
public:
	template <class E>
	class Injector : public E {
	friend class Stacktrace;
	public:
		Injector(Injector const& e)
		: E(e),
		  stacktrace(e.stacktrace ? e.stacktrace->clone() : nullptr)
		{ }

		Injector& operator=(Injector const& e)
		{
			static_cast<E&>(*this) = e;
			if(e.stacktrace) {
				stacktrace = e.stacktrace->clone();
			}
		}

	private:
	    Injector(E const & e, std::unique_ptr<Stacktrace> aStacktrace)
	    : E(e),
		  stacktrace(std::move(aStacktrace))
	    { }

		std::unique_ptr<Stacktrace> stacktrace;
	};

	Stacktrace() = default;
	virtual ~Stacktrace() = default;

	virtual void dump(std::ostream& stream) const = 0;
	virtual void dump(monitoring::Streams::Real& stream, monitoring::Streams::Location location = monitoring::Streams::Location{}) const = 0;
	inline void dump(monitoring::Streams::Empty& stream, monitoring::Streams::Location location = monitoring::Streams::Location{}) const { };

	virtual void dumpFull(std::ostream& stream) const = 0;
	virtual void dumpFull(monitoring::Streams::Real& stream, monitoring::Streams::Location location = monitoring::Streams::Location{}) const = 0;
	inline void dumpFull(monitoring::Streams::Empty& stream, monitoring::Streams::Location location = monitoring::Streams::Location{}) const { };

	virtual std::unique_ptr<Stacktrace> clone() const = 0;

	template <class E>
	static Injector<E> add(const E& e);

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

template <class E>
Stacktrace::Injector<E> Stacktrace::add(const E& e) {
	auto create = plugin::Registry::get().findObject<StacktraceFactory>();
	return Stacktrace::Injector<E>(e, create ? create->createStacktrace() : nullptr);
}

template <class E>
const Stacktrace* Stacktrace::get(const E& e) {
   	const Stacktrace::Injector<E>* injector = dynamic_cast<const Stacktrace::Injector<E> *>(&e);
   	return injector ? injector->stacktrace.get() : nullptr;
}

} /* namespace system */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_SYSTEM_STACKTRACE_H_ */
