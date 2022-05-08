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

#include <esl/boot/application/ProcedureContext.h>
#if 0
#include <jerry/engine/procedure/Context.h>

#include <stdexcept>
//#include <utility>
//#include <vector>

namespace esl {
namespace boot {
namespace application {

namespace {
jerry::engine::procedure::Context& getProcedureContext(void* object) {
	if(!object) {
		throw std::runtime_error("Null pointer exception");
	}

	return *static_cast<jerry::engine::procedure::Context*>(object);
}
} /* anonymous namespace */


ProcedureContext::ProcedureContext()
: object(new jerry::engine::procedure::Context(nullptr))
{ }

ProcedureContext::ProcedureContext(ProcedureContext&& procedureContext)
: object(procedureContext.object)
{
	procedureContext.object = nullptr;
}

ProcedureContext::~ProcedureContext() {
	if(object) {
		delete static_cast<jerry::engine::procedure::Context*>(object);
		object = nullptr;
	}
}

ProcedureContext& ProcedureContext::operator=(ProcedureContext&& procedureContext) {
	if(object) {
		delete static_cast<jerry::engine::procedure::Context*>(object);
		object = nullptr;
	}

	object = procedureContext.object;
	procedureContext.object = nullptr;

	return *this;
}

ProcedureContext::operator bool() const {
	return object != nullptr;
}

ProcedureContext& ProcedureContext::addProcedure(std::unique_ptr<esl::processing::procedure::Interface::Procedure> procedure) {
	getProcedureContext(object).addProcedure(std::move(procedure));

	return *this;
}

ProcedureContext& ProcedureContext::addProcedureContext(ProcedureContext procedureContext) {
	if(procedureContext) {
		std::unique_ptr<jerry::engine::procedure::Context> jerryProcedureContext(&getProcedureContext(procedureContext.object));
		procedureContext.object = nullptr;

		jerryProcedureContext->setParent(&getProcedureContext(object));
		jerryProcedureContext->setProcessRegistry(getProcedureContext(object).getProcessRegistry());
		getProcedureContext(object).addContext(std::move(jerryProcedureContext));
	}

	return *this;
}

ProcedureContext& ProcedureContext::addObject(const std::string& id, std::unique_ptr<esl::object::Interface::Object> aObject) {
	getProcedureContext(object).addObject(id, std::move(aObject));

	return *this;
}

} /* namespace application */
} /* namespace boot */
} /* namespace esl */
#endif
