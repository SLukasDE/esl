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

#ifndef ESL_BOOT_APPLICATION_INTERFACE_H_
#define ESL_BOOT_APPLICATION_INTERFACE_H_

#include <esl/boot/ObjectContext.h>
//#include <esl/boot/application/ProcedureContext.h>

#include <esl/Module.h>
#include <esl/module/Interface.h>
#include <esl/com/basic/client/ConnectionFactory.h>
#include <esl/com/http/client/ConnectionFactory.h>
#include <esl/database/ConnectionFactory.h>
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
namespace application {

struct Interface : esl::module::Interface {
	/* ******************************************** *
	 * type definitions required for this interface *
	 * ******************************************** */

	class Application : public virtual esl::object::Interface::Object {
	public:
		using ArgumentsByVector = esl::object::Value<std::vector<std::string>>;
		using ReturnCodeObject = esl::object::Value<int>;

		virtual Application& addData(const std::string& configuration) = 0;
		virtual Application& addFile(const boost::filesystem::path& filename) = 0;

		virtual Application& addProcedure(std::unique_ptr<esl::processing::procedure::Interface::Procedure> procedure) = 0;
//		virtual Application& addProcedureContext(ProcedureContext procedureContext) = 0;

		virtual Application& addObject(const std::string& id, std::unique_ptr<esl::object::Interface::Object> object) = 0;

		/* Helper methods */
		Application& addDatabase(const std::string& id, std::unique_ptr<esl::database::Interface::ConnectionFactory> connectionFactory) {
			return addObject(id, std::unique_ptr<esl::object::Interface::Object>(connectionFactory.release()));
		}

		Application& addBasicClient(const std::string& id, std::unique_ptr<esl::com::basic::client::Interface::ConnectionFactory> connectionFactory) {
			return addObject(id, std::unique_ptr<esl::object::Interface::Object>(connectionFactory.release()));
		}

		Application& addHttpClient(const std::string& id, std::unique_ptr<esl::com::http::client::Interface::ConnectionFactory> connectionFactory) {
			return addObject(id, std::unique_ptr<esl::object::Interface::Object>(connectionFactory.release()));
		}

		virtual Application& run(esl::object::ObjectContext& objectContext) = 0;

		/* Helper methods */
		Application& run(esl::object::ObjectContext& objectContext, int argc, const char *argv[]) {
			std::unique_ptr<ArgumentsByVector> argumentsObject(new ArgumentsByVector({}));
			for(int i=0; i<argc; ++i) {
				argumentsObject->get().push_back(argv[i]);
			}

			esl::object::Interface::Object* objectPtr = objectContext.findObject<esl::object::Interface::Object>("arguments");
			ArgumentsByVector* argumentsObjectPtr = dynamic_cast<ArgumentsByVector*>(objectPtr);

			if(argumentsObjectPtr) {
				*argumentsObjectPtr = std::move(argumentsObject->get());
			}
			else if(objectPtr == nullptr) {
				objectContext.addObject("arguments", std::unique_ptr<esl::object::Interface::Object>(argumentsObject.release()));
			}

			return run(objectContext);
		}

		Application& run() {
			ObjectContext objectContext;
			return run(objectContext);
		}

		Application& run(int argc, const char *argv[]) {
			ObjectContext objectContext;
			return run(objectContext, argc, argv);
		}

		int main(esl::object::ObjectContext& objectContext) {
			return run(objectContext).getReturnCode();
		}

		int main(esl::object::ObjectContext& objectContext, int argc, const char *argv[]) {
			return run(objectContext, argc, argv).getReturnCode();
		}

		int main() {
			return run().getReturnCode();
		}

		int main(int argc, const char *argv[]) {
			return run(argc, argv).getReturnCode();
		}

		virtual int getReturnCode() const = 0;
	};

	using Create = std::unique_ptr<Application> (*)(const std::vector<std::pair<std::string, std::string>>& settings);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-boot-application";
	}

	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	static std::unique_ptr<const esl::module::Interface> createInterface(const char* implementation, Create create) {
		return std::unique_ptr<const esl::module::Interface>(new Interface(implementation, create));
	}

	Interface(const char* implementation, Create aCreate)
	: esl::module::Interface(esl::getModule().getId(), getType(), implementation, esl::getModule().getApiVersion()),
	  create(aCreate)
	{ }

	Create create;
};

} /* namespace application */
} /* namespace boot */
} /* namespace esl */

#endif /* ESL_BOOT_APPLICATION_INTERFACE_H_ */
