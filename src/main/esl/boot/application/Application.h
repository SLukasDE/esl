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

#ifndef ESL_BOOT_APPLICATION_APPLICATION_H_
#define ESL_BOOT_APPLICATION_APPLICATION_H_

#include <esl/boot/application/Interface.h>
#include <esl/boot/application/ProcedureContext.h>
#include <esl/processing/procedure/Interface.h>

#include <esl/module/Implementation.h>

#include <boost/filesystem/path.hpp>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace esl {
namespace boot {
namespace application {

class Application final : public Interface::Application {
public:
	static module::Implementation& getDefault();

	Application(const std::vector<std::pair<std::string, std::string>>& settings = getDefault().getSettings(),
			const std::string& implementation = getDefault().getImplementation());

	Interface::Application& addData(const std::string& configuration) override;
	Interface::Application& addFile(const boost::filesystem::path& filename) override;

	Interface::Application& addProcedure(std::unique_ptr<esl::processing::procedure::Interface::Procedure> procedure) override;
	Interface::Application& addObject(const std::string& id, std::unique_ptr<esl::object::Interface::Object> object) override;

	Interface::Application& run(esl::object::ObjectContext& objectContext) override;

	int getReturnCode() const override;

private:
	std::unique_ptr<Interface::Application> application;
};

} /* namespace application */
} /* namespace boot */
} /* namespace esl */

#endif /* ESL_BOOT_APPLICATION_APPLICATION_H_ */
