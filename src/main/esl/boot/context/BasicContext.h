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
#include <esl/com/basic/client/ConnectionFactory.h>
#include <esl/com/http/client/ConnectionFactory.h>
#include <esl/database/ConnectionFactory.h>
#include <esl/object/Event.h>
#include <esl/object/Object.h>
#include <esl/object/Context.h>
#include <esl/processing/Procedure.h>
#include <esl/plugin/Registry.h>
#include <esl/plugin/Plugin.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace esl {
namespace boot {
namespace context {

template<typename T>
class BasicContext : public object::Event, public object::Context, public processing::Procedure {
public:
    T& addData(const std::string& configuration) {
    	contextPtr->addData(configuration);
		return *static_cast<T*>(this);
	}

	T& addFile(const boost::filesystem::path& filename) {
		contextPtr->addFile(filename);
		return *static_cast<T*>(this);
	}

	T& addReference(const std::string& destinationId, const std::string& sourceId) {
		contextPtr->addReference(destinationId, sourceId);
		return *static_cast<T*>(this);
	}

	int getReturnCode() const {
		return contextPtr->getReturnCode();
	}

	/* From Event: */
	void onEvent(const object::Object& object) override {
		contextPtr->onEvent(object);
	}

	/* From Context: */
	std::set<std::string> getObjectIds() const override {
		return contextPtr->getObjectIds();
	}

	/* From Procedure: */
	void procedureRun(object::Context& objectContext) override {
		contextPtr->procedureRun(objectContext);
	}

	/* Helper methods */
	template<typename U = object::Object>
	T& add(const std::string& id, std::unique_ptr<U> u) {
		contextPtr->add(id, std::move(u));
		return *static_cast<T*>(this);
	}

	template<typename U = object::Object>
	T& add(std::unique_ptr<U> u) {
		contextPtr->add(std::move(u));
		return *static_cast<T*>(this);
	}

	T& add(const std::string& id) {
		contextPtr->add(id);
		return *static_cast<T*>(this);
	}

	T& run(object::Context& objectContext) {
		contextPtr->run(objectContext);
		return *static_cast<T*>(this);
	}

	T& run(object::Context& objectContext, int argc, const char *argv[]) {
		//contextPtr->Interface::Context::run(objectContext, argc, argv);
		contextPtr->run(objectContext, argc, argv);
		return *static_cast<T*>(this);
	}

	T& run() {
		//contextPtr->Interface::Context::run();
		contextPtr->run();
		return *static_cast<T*>(this);
	}

	T& run(int argc, const char *argv[]) {
		//contextPtr->Interface::Context::run(argc, argv);
		contextPtr->run(argc, argv);
		return *static_cast<T*>(this);
	}

	int main(object::Context& objectContext) {
		return contextPtr->main(objectContext);
	}

	int main(object::Context& objectContext, int argc, const char *argv[]) {
		return contextPtr->main(objectContext, argc, argv);
	}

	int main() {
		return contextPtr->main();
	}

	int main(int argc, const char *argv[]) {
		return contextPtr->main(argc, argv);
	}

protected:
	BasicContext(const std::vector<std::pair<std::string, std::string>>& settings, const std::string& implementation)
	: contextPtr(plugin::Registry::get().create<Context>(implementation, settings))
	{ }

	/* From Context: */
	object::Object* findRawObject(const std::string& id) override {
		return contextPtr->findObject<object::Object>(id);
	}

	const object::Object* findRawObject(const std::string& id) const override {
		return contextPtr->findObject<object::Object>(id);
	}

	void addRawObject(const std::string& id, std::unique_ptr<object::Object> object) override {
		contextPtr->addObject<object::Object>(id, std::move(object));
	}

private:
	std::unique_ptr<Context> contextPtr;
};

} /* namespace context */
} /* namespace boot */
} /* namespace esl */

#endif /* ESL_BOOT_CONTEXT_BASICCONTEXT_H_ */
