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

#ifndef ESL_BOOT_CONTEXT_INTERFACE_H_
#define ESL_BOOT_CONTEXT_INTERFACE_H_

#include <esl/boot/ObjectContext.h>
#include <esl/Module.h>
#include <esl/module/Interface.h>
#include <esl/object/Event.h>
#include <esl/object/Interface.h>
#include <esl/object/Value.h>
#include <esl/object/ObjectContext.h>
#include <esl/processing/procedure/Interface.h>

#include <boost/filesystem/path.hpp>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace esl {
namespace boot {
namespace context {

struct Interface : module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class Context : public object::Event, public object::ObjectContext, public processing::procedure::Interface::Procedure {
	public:
		using ArgumentsByVector = object::Value<std::vector<std::string>>;
		using ReturnCodeObject = object::Value<int>;

		virtual Context& addData(const std::string& configuration) = 0;
		virtual Context& addFile(const boost::filesystem::path& filename) = 0;
		virtual Context& addReference(const std::string& destinationId, const std::string& sourceId) = 0;
		virtual int getReturnCode() const = 0;

		/* From Event:
		 * -------------------
		 * virtual void onEvent(const object::Interface::Object& object) = 0;
		 */

		/* From ObjectContext:
		 * -------------------
		 * virtual std::set<std::string> getObjectIds() const = 0;
		 */

		/* From Procedure:
		 * ---------------
		 * virtual void procedureRun(object::ObjectContext& objectContext) = 0;
		 */

		/* Helper methods */
		Context& run(object::ObjectContext& objectContext) {
			procedureRun(objectContext);
			return *this;
		}

		template<typename T = object::Interface::Object>
		Context& add(const std::string& id, std::unique_ptr<T> t) {
			addRawObject(id, std::move(t));
			return *this;
		}

		template<typename T = object::Interface::Object>
		Context& add(std::unique_ptr<T> t) {
			addRawObject("", std::move(t));
			return *this;
		}

		Context& add(const std::string& id) {
			return addReference("", id);
		}

		Context& run(object::ObjectContext& objectContext, int argc, const char *argv[]) {
			std::unique_ptr<ArgumentsByVector> argumentsObject(new ArgumentsByVector({}));
			for(int i=0; i<argc; ++i) {
				argumentsObject->get().push_back(argv[i]);
			}

			object::Interface::Object* objectPtr = objectContext.findObject<object::Interface::Object>("arguments");
			ArgumentsByVector* argumentsObjectPtr = dynamic_cast<ArgumentsByVector*>(objectPtr);

			if(argumentsObjectPtr) {
				*argumentsObjectPtr = std::move(argumentsObject->get());
			}
			else if(objectPtr == nullptr) {
				objectContext.addObject("arguments", std::unique_ptr<object::Interface::Object>(argumentsObject.release()));
			}

			return run(objectContext);
		}

		Context& run() {
			boot::ObjectContext objectContext;
			return run(objectContext);
		}

		Context& run(int argc, const char *argv[]) {
			boot::ObjectContext objectContext;
			return run(objectContext, argc, argv);
		}

		int main(object::ObjectContext& objectContext) {
			return run(objectContext).getReturnCode();
		}

		int main(object::ObjectContext& objectContext, int argc, const char *argv[]) {
			return run(objectContext, argc, argv).getReturnCode();
		}

		int main() {
			return run().getReturnCode();
		}

		int main(int argc, const char *argv[]) {
			return run(argc, argv).getReturnCode();
		}

	protected:
		/* From ObjectContext:
		 * -------------------
		 * virtual object::Interface::Object* findRawObject(const std::string& id) = 0;
		 * virtual const object::Interface::Object* findRawObject(const std::string& id) const = 0;
		 * virtual void addRawObject(const std::string& id, std::unique_ptr<object::Interface::Object> object) = 0;
		 */
	};

	using Create = std::unique_ptr<Context> (*)(const std::vector<std::pair<std::string, std::string>>& settings);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-boot-context";
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static std::unique_ptr<const module::Interface> createInterface(const char* implementation, Create create) {
		return std::unique_ptr<const module::Interface>(new Interface(implementation, create));
	}

	Interface(const char* implementation, Create aCreate)
	: module::Interface(getModule().getId(), getType(), implementation, getModule().getApiVersion()),
	  create(aCreate)
	{ }

	Create create;
};
/*
template<typename T = object::Interface::Object>
Interface::Context& Interface::Context::add(const std::string& id, std::unique_ptr<T> t) {
	addObject(std::unique_ptr<object::Interface::Object>(t.release()));
	return *this;
}
*/
} /* namespace context */
} /* namespace boot */
} /* namespace esl */

#endif /* ESL_BOOT_CONTEXT_INTERFACE_H_ */
