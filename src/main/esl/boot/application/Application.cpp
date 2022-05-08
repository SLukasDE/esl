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

#include <esl/boot/application/Application.h>

namespace esl {
namespace boot {
namespace application {

module::Implementation& Application::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

Application::Application(const std::vector<std::pair<std::string, std::string>>& settings, const std::string& implementation)
: application(getModule().getInterface<Interface>(implementation).create(settings))
//: application(esl::getModule().getInterface<Interface>("esl-boot/application").create(settings))
{ }

Interface::Application& Application::addData(const std::string& configuration) {
	return application->addData(configuration);
}

Interface::Application& Application::addFile(const boost::filesystem::path& filename) {
	return application->addFile(filename);
}

Interface::Application& Application::addProcedure(std::unique_ptr<esl::processing::procedure::Interface::Procedure> procedure) {
	return application->addProcedure(std::move(procedure));
}
/*
Interface::Application& Application::addProcedureContext(ProcedureContext procedureContext) {
	return application->addProcedureContext(std::move(procedureContext));
}
*/
Interface::Application& Application::addObject(const std::string& id, std::unique_ptr<esl::object::Interface::Object> aObject) {
	return application->addObject(id, std::move(aObject));
}

Interface::Application& Application::run(esl::object::ObjectContext& objectContext) {
	return application->run(objectContext);
}

int Application::getReturnCode() const {
	return application->getReturnCode();
}

} /* namespace application */
} /* namespace boot */
} /* namespace esl */
