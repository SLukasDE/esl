/*
MIT License
Copyright (c) 2019-2025 Sven Lukas

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

#ifndef ESL_PLUGIN_REGISTRY_H_
#define ESL_PLUGIN_REGISTRY_H_

#include <esl/monitoring/Logging.h>
#include <esl/object/Object.h>
#include <esl/plugin/exception/PluginNotFound.h>
#include <esl/plugin/Library.h>

#include <map>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <set>
#include <string>
#include <typeindex>
#include <utility>
#include <vector>

#define DO_QUOTE(X)                  #X
#define QUOTE(X)                     DO_QUOTE(X)

#ifndef TRANSFORMER_ARTEFACT_ID
#define TRANSFORMER_ARTEFACT_ID
//#define TRANSFORMER_ARTEFACT_ID           esl
#endif

#ifndef TRANSFORMER_ARTEFACT_NAME
#define TRANSFORMER_ARTEFACT_NAME
//#define TRANSFORMER_ARTEFACT_NAME         esl
#endif

#ifndef TRANSFORMER_ARTEFACT_VERSION
#define TRANSFORMER_ARTEFACT_VERSION
//#define TRANSFORMER_ARTEFACT_VERSION      1.0.0
#endif

#ifndef TRANSFORMER_ARTEFACT_API_VERSION
#define TRANSFORMER_ARTEFACT_API_VERSION
//#define TRANSFORMER_ARTEFACT_API_VERSION  1
#endif

#ifndef TRANSFORMER_ARTEFACT_VARIANT
#define TRANSFORMER_ARTEFACT_VARIANT
#endif

#ifndef TRANSFORMER_ARTEFACT_ARCHITECTURE
#define TRANSFORMER_ARTEFACT_ARCHITECTURE
#endif

#ifndef TRANSFORMER_ARTEFACT_LICENSE
#define TRANSFORMER_ARTEFACT_LICENSE
#endif

namespace esl {
inline namespace v1_6 {
namespace plugin {

class Registry final : public object::Object {
public:
	friend class Library;

	template <typename Interface>
	using CreateFunction = std::unique_ptr<Interface> (*)(const std::vector<std::pair<std::string, std::string>>& settings);

	template<typename Interface>
	struct Plugin : object::Object {
		Plugin(CreateFunction<Interface> aCreateFunction)
		: createFunction(aCreateFunction)
		{ }

		CreateFunction<Interface> createFunction;
	};
	using BasePlugins = std::map<std::string, std::unique_ptr<const object::Object>>;

	/* ************* *
	 * Initial stuff *
	 * ************* */

	~Registry();

	static Registry& get();
	static void set(Registry& registry);
	static void cleanup();

	void dump(std::ostream& ostream) const;


	/* ****************** *
	 * Object store stuff *
	 * ****************** */

	template <typename ObjectType>
	ObjectType* findObject();

	template <class ObjectType>
	void setObject(std::unique_ptr<ObjectType> object);


	/* ********************* *
	 * Plugin registry stuff *
	 * ********************* */

	template <typename Interface>
	std::unique_ptr<Interface> create(const std::string& implementation, const std::vector<std::pair<std::string, std::string>>& settings) const;

	const BasePlugins& getPlugins(std::type_index typeIndex) const;

	template <class Interface>
	void addPlugin(const std::string& implementation, CreateFunction<Interface> createFunction);

	template <class Interface, class ReturnValue, std::unique_ptr<ReturnValue> (*createFunction)(const std::vector<std::pair<std::string, std::string>>&)>
	void addPlugin(const std::string& implementation);

	void loadPlugin(const std::string& path, const char* data = 0);
	void loadPlugin(std::unique_ptr<Library> library, const char* data = 0);

private:
	Registry() = default;

	template <class Interface, class ReturnValue, std::unique_ptr<ReturnValue> (*createFunction)(const std::vector<std::pair<std::string, std::string>>&)>
	static std::unique_ptr<Interface> createFunctionCasted(const std::vector<std::pair<std::string, std::string>>& settings);

	std::vector<std::unique_ptr<Library>> libraries;

	using TypePlugins = std::map<std::type_index, BasePlugins>;
	TypePlugins typePlugins;

	std::map<std::type_index, std::unique_ptr<object::Object>> objects;
};


template<typename ObjectType>
ObjectType* Registry::findObject() {
	auto iter = objects.find(std::type_index(typeid(ObjectType)));
	return (iter == objects.end()) ? nullptr : static_cast<ObjectType*>(iter->second.get());
}

template <class ObjectType>
void Registry::setObject(std::unique_ptr<ObjectType> object) {
	if(std::type_index(typeid(ObjectType)) == std::type_index(typeid(monitoring::Logging))) {
		// The monitoring::Logging cannot be changed, because every Logger has a pointer to this object.
		objects.insert(std::make_pair(std::type_index(typeid(monitoring::Logging)), std::move(object)));
	}
	else if(object) {
		objects[std::type_index(typeid(ObjectType))] = std::move(object);
	}
	else {
		objects.erase(std::type_index(typeid(ObjectType)));
	}
}

template <typename Interface>
std::unique_ptr<Interface> Registry::create(const std::string& implementation, const std::vector<std::pair<std::string, std::string>>& settings) const {
	auto typePluginsIter = typePlugins.find(std::type_index(typeid(Interface)));
	if(typePluginsIter == typePlugins.end()) {
		throw plugin::exception::PluginNotFound(std::type_index(typeid(Interface)), implementation);
	}

	const BasePlugins& basePlugins = typePluginsIter->second;
	auto basePluginsIter = basePlugins.find(implementation);
	if(basePluginsIter == basePlugins.end()) {
		throw plugin::exception::PluginNotFound(std::type_index(typeid(Interface)), implementation);
	}

	const Plugin<Interface>* plugin = static_cast<const Plugin<Interface>*>(basePluginsIter->second.get());
	if(!plugin) {
		throw plugin::exception::PluginNotFound(std::type_index(typeid(Interface)), implementation);
	}

	if(!plugin->createFunction) {
		throw std::runtime_error("Cannot get factory for implementation \"" + implementation + "\" and type \"" + std::string(typeid(Interface).name()) + "\"");
	}
	return plugin->createFunction(settings);
}

template <class Interface>
void Registry::addPlugin(const std::string& implementation, CreateFunction<Interface> createFunction) {
	std::unique_ptr<const object::Object> basePlugin(new Plugin<Interface>(createFunction));
	typePlugins[std::type_index(typeid(Interface))][implementation] = std::move(basePlugin);
}

template <class Interface, class ReturnValue, std::unique_ptr<ReturnValue> (*createFunction)(const std::vector<std::pair<std::string, std::string>>&)>
void Registry::addPlugin(const std::string& implementation) {
	typePlugins[std::type_index(typeid(Interface))][implementation] = std::unique_ptr<const object::Object>(new Plugin<Interface>(createFunctionCasted<Interface, ReturnValue, createFunction>));
}

template <class Interface, class ReturnValue, std::unique_ptr<ReturnValue> (*createFunction)(const std::vector<std::pair<std::string, std::string>>&)>
std::unique_ptr<Interface> Registry::createFunctionCasted(const std::vector<std::pair<std::string, std::string>>& settings) {
	return createFunction(settings);
}

} /* namespace plugin */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_PLUGIN_REGISTRY_H_ */
