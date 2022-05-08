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

#ifndef ESL_BOOT_APPLICATION_BASICAPPLICATION_H_
#define ESL_BOOT_APPLICATION_BASICAPPLICATION_H_

#include <esl/boot/application/Application.h>
#include <esl/processing/procedure/Interface.h>
#include <esl/object/Interface.h>
#include <esl/database/Interface.h>
#include <esl/com/basic/client/Interface.h>
#include <esl/com/http/client/Interface.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace esl {
namespace boot {
namespace application {

template<typename T>
class BasicApplication {
public:
	BasicApplication(const std::vector<std::pair<std::string, std::string>>& settings)
	: impl(settings)
	{ }

    explicit operator bool() const {
    	return impl();
    }

    T& addData(const std::string& configuration) {
		impl.addData(configuration);
		return *static_cast<T*>(this);
	}

	T& addFile(const boost::filesystem::path& filename) {
		impl.addFile(filename);
		return *static_cast<T*>(this);
	}

	T& addProcedure(std::unique_ptr<esl::processing::procedure::Interface::Procedure> procedure) {
		impl.addProcedure(std::move(procedure));
		return *static_cast<T*>(this);
	}
/*
	T& addProcedureContext(ProcedureContext procedureContext) {
		impl.addProcedureContext(procedureContext);
		return *static_cast<T*>(this);
	}
*/
	T& addObject(const std::string& id, std::unique_ptr<esl::object::Interface::Object> object) {
		impl.addObject(id, std::move(object));
		return *static_cast<T*>(this);
	}

	/* Helper methods */
	T& addDatabase(const std::string& id, std::unique_ptr<esl::database::Interface::ConnectionFactory> connectionFactory) {
		impl.addDatabase(id, std::move(connectionFactory));
		return *static_cast<T*>(this);
	}

	T& addBasicClient(const std::string& id, std::unique_ptr<esl::com::basic::client::Interface::ConnectionFactory> connectionFactory) {
		impl.addBasicClient(id, std::move(connectionFactory));
		return *static_cast<T*>(this);
	}

	T& addHttpClient(const std::string& id, std::unique_ptr<esl::com::http::client::Interface::ConnectionFactory> connectionFactory) {
		impl.addHttpClient(id, std::move(connectionFactory));
		return *static_cast<T*>(this);
	}

	T& run(esl::object::ObjectContext& objectContext) {
		impl.run(objectContext);
		return *static_cast<T*>(this);
	}

	T& run(esl::object::ObjectContext& objectContext, int argc, const char *argv[]) {
		impl.Interface::Application::run(objectContext, argc, argv);
		return *static_cast<T*>(this);
	}

	T& run() {
		impl.Interface::Application::run();
		return *static_cast<T*>(this);
	}

	T& run(int argc, const char *argv[]) {
		impl.Interface::Application::run(argc, argv);
		return *static_cast<T*>(this);
	}

	/* Helper methods */
	int main(esl::object::ObjectContext& objectContext) {
		return impl.main(objectContext);
	}

	int main(esl::object::ObjectContext& objectContext, int argc, const char *argv[]) {
		return impl.main(objectContext, argc, argv);
	}

	int main() {
		return impl.main();
	}

	int main(int argc, const char *argv[]) {
		return impl.main(argc, argv);
	}

	int getReturnCode() const {
		return impl.getReturnCode();
	}

private:
	Application impl;
};

} /* namespace application */
} /* namespace boot */
} /* namespace esl */

#endif /* ESL_BOOT_APPLICATION_BASICAPPLICATION_H_ */
