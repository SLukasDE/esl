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

#ifndef ESL_UTILITY_UNIQUEREF_H_
#define ESL_UTILITY_UNIQUEREF_H_

#include <esl/system/stacktrace/IStacktrace.h>

#include <memory>
#include <stdexcept>

namespace esl {
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
            throw system::stacktrace::IStacktrace::add(std::runtime_error("Initialization of esl::utility::UniqueRef with nullptr"));
        }
    }

	UniqueRef(std::unique_ptr<T> aValue)
    : value(std::move(aValue))
    {
        if(!value) {
            throw system::stacktrace::IStacktrace::add(std::runtime_error("Initialization of esl::utility::UniqueRef with nullptr"));
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

	const T& operator->() const noexcept {
		return *value;
	}

	T& operator->() noexcept {
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
} /* namespace esl */

#endif /* ESL_UTILITY_UNIQUEREF_H_ */
