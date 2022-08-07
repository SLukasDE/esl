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

#ifndef ESL_PLUGIN_REGISTRY_H_
#define ESL_PLUGIN_REGISTRY_H_

#include <esl/plugin/BasePlugin.h>
#include <esl/plugin/exception/PluginNotFound.h>
#include <esl/plugin/Library.h>
#include <esl/plugin/Plugin.h>
#include <esl/logging/Logging.h>

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
namespace system {
class Stacktrace;
} /* namespace system */
} /* namespace esl */

namespace esl {
namespace plugin {

class Registry final {
	friend class logging::Logging;
	friend class system::Stacktrace;
	friend class Library;
public:
	template <typename Interface>
	using Factory = std::unique_ptr<Interface> (*)(const std::vector<std::pair<std::string, std::string>>& settings);

	using StacktraceFactory = Factory<system::Stacktrace>;

	using BasePlugins = std::map<std::string, std::unique_ptr<const BasePlugin>>;

	~Registry();

	static Registry& get();
	static void set(Registry& registry);
	static void cleanup();

	void dump(std::ostream& ostream) const;

	template <typename Interface>
	std::unique_ptr<Interface> create() const;

	template <typename Interface>
	std::unique_ptr<Interface> create(const std::string& implementation, const std::vector<std::pair<std::string, std::string>>& settings) const;

	template <class Interface>
	const BasePlugins& getPlugins() const;
	const BasePlugins& getPlugins(std::type_index typeIndex) const;

	template <typename Interface>
	const Factory<Interface> findFactory() const noexcept;

	template <typename Interface>
	const Factory<Interface> findFactory(const std::string& implementation) const noexcept;

	template <typename Interface>
	const Factory<Interface> getFactory() const;

	template <typename Interface>
	const Factory<Interface> getFactory(const std::string& implementation) const;

	template <class Interface>
	const Plugin<Interface>* findPlugin() const noexcept;

	template <class Interface>
	const Plugin<Interface>* findPlugin(const std::string& implementation) const noexcept;

	template <class Interface>
	const Plugin<Interface>& getPlugin() const;

	template <class Interface>
	const Plugin<Interface>& getPlugin(const std::string& implementation) const;

	template <class Interface>
	void addPlugin(const std::string& implementation, std::unique_ptr<Interface> (*create)(const std::vector<std::pair<std::string, std::string>>&));

	template <class Interface>
	void copyPlugin(const std::string& implementationSource, const std::string& implementationDestination);

	void loadPlugin(const std::string& path, const char* data = 0);
	void loadPlugin(std::unique_ptr<Library> library, const char* data = 0);

private:
	Registry() = default;

	const BasePlugin* findBasePlugin(const std::string& implementation, std::type_index typeIndex) const noexcept;
	const BasePlugin* findBasePlugin(std::type_index typeIndex) const noexcept;

	static StacktraceFactory getStacktraceFactory();
	static const std::vector<std::pair<std::string, std::string>>& getStacktraceSettings();
	static void setStacktraceFactory(StacktraceFactory create, std::vector<std::pair<std::string, std::string>> settings);

	static logging::Logging* getLogging();
	static void setLogging(std::unique_ptr<logging::Logging> logging);

	std::vector<std::unique_ptr<Library>> libraries;

	using TypePlugins = std::map<std::type_index, BasePlugins>;
	TypePlugins typePlugins;

	StacktraceFactory stacktraceFactory = nullptr;
	std::vector<std::pair<std::string, std::string>> stacktraceSettings;

	std::unique_ptr<logging::Logging> logging;
};


template <typename Interface>
std::unique_ptr<Interface> Registry::create() const {
	return getFactory<Interface>()(std::vector<std::pair<std::string, std::string>>());
}

template <typename Interface>
std::unique_ptr<Interface> Registry::create(const std::string& implementation, const std::vector<std::pair<std::string, std::string>>& settings) const {
	return getFactory<Interface>(implementation)(settings);
}

template <class Interface>
const Registry::BasePlugins& Registry::getPlugins() const {
	return getPlugins(typeid(Interface));
}

template <typename Interface>
const Registry::Factory<Interface> Registry::findFactory() const noexcept {
	const Plugin<Interface>* plugin = findPlugin<Interface>();
	return plugin ? plugin->create : nullptr;
}

template <typename Interface>
const Registry::Factory<Interface> Registry::findFactory(const std::string& implementation) const noexcept {
	const Plugin<Interface>* plugin = findPlugin<Interface>(implementation);
	return plugin ? plugin->create : nullptr;
}

template <typename Interface>
const Registry::Factory<Interface> Registry::getFactory() const {
	const Plugin<Interface>* plugin = findPlugin<Interface>();
	if(!plugin) {
		throw plugin::exception::PluginNotFound(typeid(Interface));
	}

	if(!plugin->create) {
		throw std::runtime_error("Cannot get factory for type \"" + std::string(typeid(Interface).name()) + "\"");
	}
	return plugin->create;
}

template <typename Interface>
const Registry::Factory<Interface> Registry::getFactory(const std::string& implementation) const {
	const Plugin<Interface>* plugin = findPlugin<Interface>(implementation);
	if(!plugin) {
		throw plugin::exception::PluginNotFound(typeid(Interface), implementation);
	}

	if(!plugin->create) {
		throw std::runtime_error("Cannot get factory for implementation \"" + implementation + "\" and type \"" + std::string(typeid(Interface).name()) + "\"");
	}
	return plugin->create;
}

template <class Interface>
const Plugin<Interface>* Registry::findPlugin() const noexcept {
	return static_cast<const Plugin<Interface>*>(findBasePlugin(typeid(Interface)));
}

template <class Interface>
const Plugin<Interface>* Registry::findPlugin(const std::string& implementation) const noexcept {
	return static_cast<const Plugin<Interface>*>(findBasePlugin(implementation, typeid(Interface)));
}

template <class Interface>
const Plugin<Interface>& Registry::getPlugin() const {
	const Plugin<Interface>* plugin = findPlugin<Interface>();

	if(plugin == nullptr) {
		throw plugin::exception::PluginNotFound(typeid(Interface));
	}

	return *plugin;
}

template <class Interface>
const Plugin<Interface>& Registry::getPlugin(const std::string& implementation) const {
	const Plugin<Interface>* plugin = findPlugin<Interface>(implementation);

	if(plugin == nullptr) {
		throw plugin::exception::PluginNotFound(typeid(Interface), implementation);
	}

	return *plugin;
}

template <class Interface>
void Registry::addPlugin(const std::string& implementation, std::unique_ptr<Interface> (*create)(const std::vector<std::pair<std::string, std::string>>&)) {
	std::unique_ptr<const BasePlugin> basePlugin(new Plugin<Interface>(implementation, create));
	typePlugins[typeid(Interface)][implementation] = std::move(basePlugin);
}

template <class Interface>
void Registry::copyPlugin(const std::string& implementationSource, const std::string& implementationDestination) {
	addPlugin<Interface>(implementationDestination, getPlugin<Interface>(implementationSource).create);
}

} /* namespace plugin */
} /* namespace esl */

#endif /* ESL_PLUGIN_REGISTRY_H_ */
