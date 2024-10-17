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

#ifndef ESL_OBJECT_VALUE_H_
#define ESL_OBJECT_VALUE_H_

#include <esl/object/Object.h>
#include <esl/object/Cloneable.h>

#include <memory>

namespace esl {
inline namespace v1_6 {
namespace object {

template <typename T>
class Value : public Cloneable {
public:
	Value(const T& aValue)
	: value(aValue)
	{ }

	Value(T&& aValue)
	: value(std::move(aValue))
	{ }

	std::unique_ptr<Cloneable> clone() const override {
		return std::unique_ptr<Cloneable>(new Value<T>(value));
	}

	T& operator=(const T& aValue) {
		value = aValue;
		return value;
	}

	T& operator=(T&& aValue) {
		value = std::move(aValue);
		return value;
	}

	const T& operator*() const noexcept {
		return value;
	}

	T& operator*() noexcept {
		return value;
	}

	const T* operator->() const noexcept {
		return value;
	}

	T* operator->() noexcept {
		return value;
	}

	const T& get() const noexcept {
		return value;
	}

	T& get() noexcept {
		return value;
	}

private:
	T value;
};

} /* namespace object */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_OBJECT_VALUE_H_ */
