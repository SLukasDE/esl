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

#ifndef ESL_PROCESSING_PROCEDURE_INTERFACE_H_
#define ESL_PROCESSING_PROCEDURE_INTERFACE_H_

#include <esl/module/Interface.h>
//#include <esl/object/Event.h>
#include <esl/object/Interface.h>
#include <esl/object/Context.h>
#include <esl/Module.h>

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace esl {
namespace processing {
namespace procedure {

struct Interface : module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class Procedure : public virtual object::Interface::Object {
	public:
		/* this method is blocking. */
		//virtual std::unique_ptr<object::Context> procedureRun(object::Context& context) = 0;
		virtual void procedureRun(object::Context& context) = 0;

		/* this method is non-blocking. */
		virtual void procedureCancel() { };
	};

	using CreateProcedure = std::unique_ptr<Procedure> (*)(const std::vector<std::pair<std::string, std::string>>& settings);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-processing-procedure";
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static std::unique_ptr<const module::Interface> createInterface(const char* implementation, CreateProcedure createProcedure) {
		return std::unique_ptr<const module::Interface>(new Interface(implementation, createProcedure));
	}

	Interface(const char* implementation, CreateProcedure aCreateProcedure)
	: module::Interface(getModule().getId(), getType(), implementation, getModule().getApiVersion()),
	  createProcedure(aCreateProcedure)
	{ }

	CreateProcedure createProcedure;
};

} /* namespace procedure */
} /* namespace processing */
} /* namespace esl */

#endif /* ESL_PROCESSING_PROCEDURE_INTERFACE_H_ */
