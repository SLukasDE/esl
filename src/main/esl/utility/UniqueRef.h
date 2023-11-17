/*
 * This file is part of ESL.
 * Copyright (C) 2020-2023 Sven Lukas
 *
 * ESL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ESL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License
 * along with ESL.  If not, see <https://www.gnu.org/licenses/>.
 */

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
