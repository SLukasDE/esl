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

#include <esl/processing/procedure/Procedure.h>
#include <esl/utility/Event.h>
#include <esl/Module.h>

namespace esl {
namespace processing {
namespace procedure {

module::Implementation& Procedure::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

Procedure::Procedure(const std::vector<std::pair<std::string, std::string>>& settings, const std::string& implementation)
: procedure(getModule().getInterface<Interface>(implementation).createProcedure(settings))
{ }
/*
std::unique_ptr<object::Context> Procedure::procedureRun(object::Context& context) {
	return procedure->procedureRun(objectContext);
}
*/
void Procedure::procedureRun(object::Context& context) {
	procedure->procedureRun(context);
}

void Procedure::procedureCancel() {
	procedure->procedureCancel();
}

} /* namespace procedure */
} /* namespace processing */
} /* namespace esl */
