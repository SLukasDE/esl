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

#ifndef ESL_BOOT_CONTEXT_BASICCONTEXT_H_
#define ESL_BOOT_CONTEXT_BASICCONTEXT_H_

#include <esl/boot/context/Context.h>
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
namespace context {

template<typename T>
class BasicContext {
public:
	BasicContext(const std::vector<std::pair<std::string, std::string>>& settings = Context::getDefault().getSettings(),
			const std::string& implementation = Context::getDefault().getImplementation())
	: context(settings, implementation)
	{ }

    T& addData(const std::string& configuration) {
    	context.addData(configuration);
		return *static_cast<T*>(this);
	}

	T& addFile(const boost::filesystem::path& filename) {
		context.addFile(filename);
		return *static_cast<T*>(this);
	}

	T& addProcedure(std::unique_ptr<processing::procedure::Interface::Procedure> procedure) {
		context.addProcedure(std::move(procedure));
		return *static_cast<T*>(this);
	}

	T& add(const std::string& id, std::unique_ptr<object::Interface::Object> object) {
		context.add(id, std::move(object));
		return *static_cast<T*>(this);
	}

	/* Helper methods */
	T& add(const std::string& id, std::unique_ptr<database::Interface::ConnectionFactory> connectionFactory) {
		context.add(id, std::move(connectionFactory));
		return *static_cast<T*>(this);
	}

	T& add(const std::string& id, std::unique_ptr<com::basic::client::Interface::ConnectionFactory> connectionFactory) {
		context.add(id, std::move(connectionFactory));
		return *static_cast<T*>(this);
	}

	T& add(const std::string& id, std::unique_ptr<com::http::client::Interface::ConnectionFactory> connectionFactory) {
		context.add(id, std::move(connectionFactory));
		return *static_cast<T*>(this);
	}

	T& run(object::ObjectContext& objectContext) {
		context.run(objectContext);
		return *static_cast<T*>(this);
	}

	T& run(object::ObjectContext& objectContext, int argc, const char *argv[]) {
		context.Interface::Context::run(objectContext, argc, argv);
		return *static_cast<T*>(this);
	}

	T& run() {
		context.Interface::Context::run();
		return *static_cast<T*>(this);
	}

	T& run(int argc, const char *argv[]) {
		context.Interface::Context::run(argc, argv);
		return *static_cast<T*>(this);
	}

	/* Helper methods */
	int main(object::ObjectContext& objectContext) {
		return context.main(objectContext);
	}

	int main(object::ObjectContext& objectContext, int argc, const char *argv[]) {
		return context.main(objectContext, argc, argv);
	}

	int main() {
		return context.main();
	}

	int main(int argc, const char *argv[]) {
		return context.main(argc, argv);
	}

	int getReturnCode() const {
		return context.getReturnCode();
	}

	void addObject(const std::string& id, std::unique_ptr<object::Interface::Object> object) {
		context.addObject(id, std::move(object));
	}

	std::set<std::string> getObjectIds() const {
		return context.getObjectIds();
	}

private:
	Context context;
};

} /* namespace context */
} /* namespace boot */
} /* namespace esl */

#endif /* ESL_BOOT_CONTEXT_BASICCONTEXT_H_ */
