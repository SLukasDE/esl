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

#include <esl/utility/ScopeGuard.h>

namespace esl {
inline namespace v1_6 {
namespace utility {

ScopeGuard::ScopeGuard(std::function<void()> aLambda)
: lambda(aLambda),
  isEmpty(false)
{ }

ScopeGuard::ScopeGuard(ScopeGuard&& other)
: lambda(std::move(other.lambda)),
  isEmpty(false)
{
	other.isEmpty = true;
}

ScopeGuard::~ScopeGuard() {
	if(!isEmpty) {
		lambda();
	}
}

ScopeGuard& ScopeGuard::operator=(ScopeGuard&& other) {
	lambda = std::move(other.lambda);
	isEmpty = false;
	other.isEmpty = true;
	return *this;
}

void ScopeGuard::clear() {
	isEmpty = true;
}

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */
