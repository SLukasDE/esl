#include <esl/object/Object.h>
#include <esl/object/ProcessingContext.h>
#include <esl/object/Value.h>

#include <map>
#include <memory>
#include <set>

namespace esl {
inline namespace v1_6 {
namespace object {

namespace {
using ArgumentsByVector = Value<std::vector<std::string>>;
using ReturnCodeObject = Value<int>;

class ObjectContext final : public Context {
public:
	void addObject(const std::string& id, std::unique_ptr<Object> object) override {
		objects[id] = std::move(object);
	}

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

private:
	std::map<std::string, std::unique_ptr<Object>> objects;
};

} /* anonymous namespace */


void ProcessingContext::run(Context& objectContext, int argc, const char *argv[]) {
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

	procedureRun(objectContext);
}

void ProcessingContext::run() {
	ObjectContext objectContext;
	procedureRun(objectContext);
}

void ProcessingContext::run(int argc, const char *argv[]) {
	ObjectContext objectContext;
	run(objectContext, argc, argv);
}

int ProcessingContext::main(Context& objectContext) {
	procedureRun(objectContext);
	return getReturnCode();
}

int ProcessingContext::main(Context& objectContext, int argc, const char *argv[]) {
	run(objectContext, argc, argv);
	return getReturnCode();
}

int ProcessingContext::main() {
	run();
	return getReturnCode();
}

int ProcessingContext::main(int argc, const char *argv[]) {
	run(argc, argv);
	return getReturnCode();
}

} /* namespace object */
} /* inline namespace v1_6 */
} /* namespace esl */
