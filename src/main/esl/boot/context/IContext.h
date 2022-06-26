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

#ifndef ESL_BOOT_CONTEXT_ICONTEXT_H_
#define ESL_BOOT_CONTEXT_ICONTEXT_H_

#include <esl/boot/ObjectContext.h>
#include <esl/object/IEvent.h>
#include <esl/object/IObject.h>
#include <esl/object/Value.h>
#include <esl/object/IContext.h>
#include <esl/plugin/Plugin.h>
#include <esl/processing/procedure/IProcedure.h>

#include <boost/filesystem/path.hpp>

#include <memory>
#include <string>
//#include <utility>
#include <vector>

namespace esl {
namespace boot {
namespace context {

class IContext : public object::IEvent, public object::IContext, public processing::procedure::IProcedure {
public:
	using Plugin = plugin::Plugin<IContext>;

	using ArgumentsByVector = object::Value<std::vector<std::string>>;
	using ReturnCodeObject = object::Value<int>;

	virtual IContext& addData(const std::string& configuration) = 0;
	virtual IContext& addFile(const boost::filesystem::path& filename) = 0;
	virtual IContext& addReference(const std::string& destinationId, const std::string& sourceId) = 0;
	virtual int getReturnCode() const = 0;

	/* From Event:
	 * -------------------
	 * virtual void onEvent(const object::IObject& object) = 0;
	 */

	/* From Context:
	 * -------------------
	 * virtual std::set<std::string> getObjectIds() const = 0;
	 */

	/* From Procedure:
	 * ---------------
	 * virtual void procedureRun(object::Context& objectContext) = 0;
	 */

	/* Helper methods */
	template<typename T = object::IObject>
	IContext& add(const std::string& id, std::unique_ptr<T> t) {
		addRawObject(id, std::move(t));
		return *this;
	}

	template<typename T = object::IObject>
	IContext& add(std::unique_ptr<T> t) {
		addRawObject("", std::move(t));
		return *this;
	}

	IContext& add(const std::string& id) {
		return addReference("", id);
	}

	IContext& run(object::IContext& objectContext) {
		procedureRun(objectContext);
		return *this;
	}

	IContext& run(object::IContext& objectContext, int argc, const char *argv[]) {
		std::unique_ptr<ArgumentsByVector> argumentsObject(new ArgumentsByVector({}));
		for(int i=0; i<argc; ++i) {
			argumentsObject->get().push_back(argv[i]);
		}

		object::IObject* objectPtr = objectContext.findObject<object::IObject>("arguments");
		ArgumentsByVector* argumentsObjectPtr = dynamic_cast<ArgumentsByVector*>(objectPtr);

		if(argumentsObjectPtr) {
			*argumentsObjectPtr = std::move(argumentsObject->get());
		}
		else if(objectPtr == nullptr) {
			objectContext.addObject("arguments", std::unique_ptr<object::IObject>(argumentsObject.release()));
		}

		return run(objectContext);
	}

	IContext& run() {
		boot::ObjectContext objectContext;
		return run(objectContext);
	}

	IContext& run(int argc, const char *argv[]) {
		boot::ObjectContext objectContext;
		return run(objectContext, argc, argv);
	}

	int main(object::IContext& objectContext) {
		return run(objectContext).getReturnCode();
	}

	int main(object::IContext& objectContext, int argc, const char *argv[]) {
		return run(objectContext, argc, argv).getReturnCode();
	}

	int main() {
		return run().getReturnCode();
	}

	int main(int argc, const char *argv[]) {
		return run(argc, argv).getReturnCode();
	}

protected:
	/* From Context:
	 * -------------------
	 * virtual object::IObject* findRawObject(const std::string& id) = 0;
	 * virtual const object::IObject* findRawObject(const std::string& id) const = 0;
	 * virtual void addRawObject(const std::string& id, std::unique_ptr<object::IObject> object) = 0;
	 */
};

} /* namespace context */
} /* namespace boot */
} /* namespace esl */

#endif /* ESL_BOOT_CONTEXT_ICONTEXT_H_ */
