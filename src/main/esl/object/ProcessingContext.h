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

#ifndef ESL_OBJECT_PROCESSINGCONTEXT_H_
#define ESL_OBJECT_PROCESSINGCONTEXT_H_

#include <esl/object/Context.h>

#include <esa/object/ProcessingContext.h>

namespace esl {
inline namespace v1_6 {
namespace object {

class ProcessingContext : public esa::object::ProcessingContext {
public:
	void run(Context& objectContext, int argc, const char *argv[]);
	void run();
	void run(int argc, const char *argv[]);

	int main(Context& objectContext);
	int main(Context& objectContext, int argc, const char *argv[]);
	int main();
	int main(int argc, const char *argv[]);
};

} /* namespace object */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_OBJECT_PROCESSINGCONTEXT_H_ */
