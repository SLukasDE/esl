/*
 * This file is part of ESL.
 * Copyright (C) 2020-2023 Sven Lukas
 *
 * ESL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ESL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License
 * along with ESL.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef ESL_UTILITY_BASICPROCESSINGCONTEXT_H_
#define ESL_UTILITY_BASICPROCESSINGCONTEXT_H_

#include <esl/com/basic/client/ConnectionFactory.h>
#include <esl/com/http/client/ConnectionFactory.h>
#include <esl/database/ConnectionFactory.h>
#include <esl/object/Context.h>
#include <esl/object/Event.h>
#include <esl/object/Object.h>
#include <esl/object/Procedure.h>
#include <esl/object/ProcessingContext.h>
#include <esl/plugin/Registry.h>
#include <esl/plugin/Plugin.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace esl {
inline namespace v1_6 {
namespace utility {

template<typename T>
class BasicContext : public esl::object::Event, public esl::object::Context, public esl::object::Procedure {
public:
    T& addData(const std::string& configuration) {
    	contextPtr->addData(configuration);
		return *static_cast<T*>(this);
	}

	T& addFile(const boost::filesystem::path& filename) {
		contextPtr->addFile(filename);
		return *static_cast<T*>(this);
	}

	T& addAlias(const std::string& destinationId, const std::string& sourceId) {
		contextPtr->addAlias(destinationId, sourceId);
		return *static_cast<T*>(this);
	}

	T& addReference(const std::string& sourceId) {
		contextPtr->addReference(sourceId);
		return *static_cast<T*>(this);
	}

	int getReturnCode() const {
		return contextPtr->getReturnCode();
	}

	/* From Event: */
	void onEvent(const esl::object::Object& object) override {
		contextPtr->onEvent(object);
	}

	/* From Context: */
	std::set<std::string> getObjectIds() const override {
		return contextPtr->getObjectIds();
	}

	/* From Procedure: */
	void procedureRun(esl::object::Context& objectContext) override {
		contextPtr->procedureRun(objectContext);
	}

	/* Helper methods */
	template<typename U = esa::object::Object>
	T& add(const std::string& id, std::unique_ptr<U> u) {
		contextPtr->add(id, std::move(u));
		return *static_cast<T*>(this);
	}

	template<typename U = esa::object::Object>
	T& add(std::unique_ptr<U> u) {
		contextPtr->add(std::move(u));
		return *static_cast<T*>(this);
	}

	T& add(const std::string& id) {
		contextPtr->add(id);
		return *static_cast<T*>(this);
	}

	T& run(esl::object::Context& objectContext) {
		contextPtr->run(objectContext);
		return *static_cast<T*>(this);
	}

	T& run(esl::object::Context& objectContext, int argc, const char *argv[]) {
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

	int main(esl::object::Context& objectContext) {
		return contextPtr->main(objectContext);
	}

	int main(esl::object::Context& objectContext, int argc, const char *argv[]) {
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
	: contextPtr(plugin::Registry::get().create<esl::object::ProcessingContext>(implementation, settings))
	{ }

	/* From Context: */
	esl::object::Object* findRawObject(const std::string& id) override {
		return contextPtr->findObject<esl::object::Object>(id);
	}

	const esl::object::Object* findRawObject(const std::string& id) const override {
		return contextPtr->findObject<esl::object::Object>(id);
	}

	void addRawObject(const std::string& id, std::unique_ptr<esl::object::Object> object) override {
		contextPtr->addObject<esl::object::Object>(id, std::move(object));
	}

private:
	std::unique_ptr<esl::object::ProcessingContext> contextPtr;
};

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_UTILITY_BASICPROCESSINGCONTEXT_H_ */
