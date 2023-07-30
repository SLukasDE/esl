/*
MIT License
Copyright (c) 2019-2023 Sven Lukas

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

#include <esl/object/ProcessingContext.h>

#include <map>
#include <set>


namespace esl {
inline namespace v1_6 {
namespace object {

namespace {

class ObjectContext final : public Context {
public:
	std::set<std::string> getObjectIds() const override {
		std::set<std::string> rv;

		for(const auto& object : objects) {
			rv.insert(object.first);
		}

		return rv;
	}

protected:
	Object* findRawObject(const std::string& id) override {
		auto iter = objects.find(id);
		return iter == std::end(objects) ? nullptr : iter->second.get();
	}

	const Object* findRawObject(const std::string& id) const override {
		auto iter = objects.find(id);
		return iter == std::end(objects) ? nullptr : iter->second.get();
	}

	void addRawObject(const std::string& id, std::unique_ptr<Object> object) override {
		objects[id] = std::move(object);
	}

private:
	std::map<std::string, std::unique_ptr<Object>> objects;
};

} /* anonymous namespace */

ProcessingContext& ProcessingContext::add(const std::string& id) {
	return addReference("", id);
}

ProcessingContext& ProcessingContext::run(Context& objectContext) {
	procedureRun(objectContext);
	return *this;
}

ProcessingContext& ProcessingContext::run(Context& objectContext, int argc, const char *argv[]) {
	std::unique_ptr<ArgumentsByVector> argumentsObject(new ArgumentsByVector({}));
	for(int i=0; i<argc; ++i) {
		argumentsObject->get().push_back(argv[i]);
	}

	Object* objectPtr = objectContext.findObject<Object>("arguments");
	ArgumentsByVector* argumentsObjectPtr = dynamic_cast<ArgumentsByVector*>(objectPtr);

	if(argumentsObjectPtr) {
		*argumentsObjectPtr = std::move(argumentsObject->get());
	}
	else if(objectPtr == nullptr) {
		objectContext.addObject("arguments", std::unique_ptr<Object>(argumentsObject.release()));
	}

	return run(objectContext);
}

ProcessingContext& ProcessingContext::run() {
	ObjectContext objectContext;
	return run(objectContext);
}

ProcessingContext& ProcessingContext::run(int argc, const char *argv[]) {
	ObjectContext objectContext;
	return run(objectContext, argc, argv);
}

int ProcessingContext::main(Context& objectContext) {
	return run(objectContext).getReturnCode();
}

int ProcessingContext::main(Context& objectContext, int argc, const char *argv[]) {
	return run(objectContext, argc, argv).getReturnCode();
}

int ProcessingContext::main() {
	return run().getReturnCode();
}

int ProcessingContext::main(int argc, const char *argv[]) {
	return run(argc, argv).getReturnCode();
}

} /* namespace object */
} /* inline namespace v1_6 */
} /* namespace esl */
