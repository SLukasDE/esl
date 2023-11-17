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

#ifndef ESL_UTILITY_REFPROCEDURE_H_
#define ESL_UTILITY_REFPROCEDURE_H_

#include <esl/object/Context.h>
#include <esl/object/Procedure.h>

namespace esl {
inline namespace v1_6 {
namespace utility {

class RefProcedure final : public object::Procedure {
public:
	RefProcedure(Procedure& aRefProcedure);

	void procedureRun(object::Context& context) override;
	void procedureCancel() override;

private:
	Procedure& refProcedure;
};

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_REFPROCEDURE_H_ */
