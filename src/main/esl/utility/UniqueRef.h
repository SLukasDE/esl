#ifndef ESL_UTILITY_UNIQUEREF_H_
#define ESL_UTILITY_UNIQUEREF_H_

#include <esl/system/Stacktrace.h>

#include <memory>
#include <stdexcept>

namespace esl {
inline namespace v1_6 {
namespace utility {

template <typename T>
class UniqueRef {
public:
	UniqueRef(const T& aValue) = delete;
	UniqueRef(T&& aValue) = delete;

	UniqueRef(T* aValue)
    : value(aValue)
    {
        if(!value) {
            throw system::Stacktrace::add(std::runtime_error("Initialization of esl::utility::UniqueRef with nullptr"));
        }
    }

	UniqueRef(std::unique_ptr<T> aValue)
    : value(std::move(aValue))
    {
        if(!value) {
            throw system::Stacktrace::add(std::runtime_error("Initialization of esl::utility::UniqueRef with nullptr"));
        }
    }

	T& operator=(const T& aValue) = delete;
	T& operator=(T&& aValue) = delete;

	const T& operator*() const noexcept {
		return *value;
	}

	T& operator*() noexcept {
		return *value;
	}

	const T* operator->() const noexcept {
		return *value;
	}

	T* operator->() noexcept {
		return *value;
	}

	const T& get() const noexcept {
		return *value;
	}

	T& get() noexcept {
		return *value;
	}

private:
	std::unique_ptr<T> value;
};


} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_UNIQUEREF_H_ */
