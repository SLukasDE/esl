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
#include <esl/com/basic/client/Interface.h>
#include <esl/com/http/client/Interface.h>
#include <esl/database/Interface.h>
#include <esl/object/Event.h>
#include <esl/object/Interface.h>
#include <esl/object/Context.h>
#include <esl/processing/procedure/Interface.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace esl {
namespace boot {
namespace context {

template<typename T>
class BasicContext : public esl::object::Event, public object::Context, public processing::procedure::Interface::Procedure {
public:
    T& addData(const std::string& configuration) {
    	context.addData(configuration);
		return *static_cast<T*>(this);
	}

	T& addFile(const boost::filesystem::path& filename) {
		context.addFile(filename);
		return *static_cast<T*>(this);
	}

	T& addReference(const std::string& destinationId, const std::string& sourceId) {
		context.addReference(destinationId, sourceId);
		return *static_cast<T*>(this);
	}

	int getReturnCode() const {
		return context.getReturnCode();
	}

	/* From Event: */
	void onEvent(const object::Interface::Object& object) override {
		context.onEvent(object);
	}

	/* From Context: */
	std::set<std::string> getObjectIds() const override {
		return context.getObjectIds();
	}

	/* From Procedure: */
	void procedureRun(object::Context& objectContext) override {
		context.procedureRun(objectContext);
	}

	/* Helper methods */
	template<typename U = object::Interface::Object>
	T& add(const std::string& id, std::unique_ptr<U> u) {
		context.add(id, std::move(u));
		return *static_cast<T*>(this);
	}

	template<typename U = object::Interface::Object>
	T& add(std::unique_ptr<U> u) {
		context.add(std::move(u));
		return *static_cast<T*>(this);
	}

	T& add(const std::string& id) {
		context.add(id);
		return *static_cast<T*>(this);
	}

	T& run(object::Context& objectContext) {
		context.run(objectContext);
		return *static_cast<T*>(this);
	}

	T& run(object::Context& objectContext, int argc, const char *argv[]) {
		//context.Interface::Context::run(objectContext, argc, argv);
		context.run(objectContext, argc, argv);
		return *static_cast<T*>(this);
	}

	T& run() {
		//context.Interface::Context::run();
		context.run();
		return *static_cast<T*>(this);
	}

	T& run(int argc, const char *argv[]) {
		//context.Interface::Context::run(argc, argv);
		context.run(argc, argv);
		return *static_cast<T*>(this);
	}

	int main(object::Context& objectContext) {
		return context.main(objectContext);
	}

	int main(object::Context& objectContext, int argc, const char *argv[]) {
		return context.main(objectContext, argc, argv);
	}

	int main() {
		return context.main();
	}

	int main(int argc, const char *argv[]) {
		return context.main(argc, argv);
	}

protected:
	BasicContext(const std::vector<std::pair<std::string, std::string>>& settings = context::Context::getDefault().getSettings(),
			const std::string& implementation = context::Context::getDefault().getImplementation())
	: context(settings, implementation)
	{ }

	/* From Context: */
	object::Interface::Object* findRawObject(const std::string& id) override {
		return context.findObject<object::Interface::Object>(id);
	}

	const object::Interface::Object* findRawObject(const std::string& id) const override {
		return context.findObject<object::Interface::Object>(id);
	}

	void addRawObject(const std::string& id, std::unique_ptr<object::Interface::Object> object) override {
		context.addObject<object::Interface::Object>(id, std::move(object));
	}

private:
	context::Context context;
};

} /* namespace context */
} /* namespace boot */
} /* namespace esl */

#endif /* ESL_BOOT_CONTEXT_BASICCONTEXT_H_ */
