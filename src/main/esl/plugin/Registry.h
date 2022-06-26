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

#include <esl/plugin/Plugin.h>

#include <map>
#include <memory>
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
namespace plugin {

class Registry final {
	friend class Library;
public:
	Registry() = default;
	virtual ~Registry() = default;

	static Registry& get();
	static void set(Registry& registry);

	template<typename T, typename TPlugin>
	static std::unique_ptr<T> create(const std::vector<std::pair<std::string, std::string>>& settings, const std::string& implementation);
#if 0
	const std::string& getId() const;
	const std::string& getName() const;
	const std::string& getVariant() const;
	const std::string& getVersion() const;
	const std::string& getApiVersion() const;
	const std::string& getArchitecture() const;
	const std::string& getLicense() const;
#endif

	static inline void initialize(Registry& registry) {
#if 0
		registry.id = QUOTE(TRANSFORMER_ARTEFACT_ID);
		registry.name = QUOTE(TRANSFORMER_ARTEFACT_NAME);
		registry.variant = QUOTE(TRANSFORMER_ARTEFACT_VARIANT);
		registry.version = QUOTE(TRANSFORMER_ARTEFACT_VERSION);
		registry.apiVersion = QUOTE(TRANSFORMER_ARTEFACT_API_VERSION);
		registry.architecture = QUOTE(TRANSFORMER_ARTEFACT_ARCHITECTURE);
		registry.license = QUOTE(TRANSFORMER_ARTEFACT_LICENSE);
#endif
	}

	const std::vector<BasePlugin>& getMetaPlugins() const;

	const BasePlugin* findBasePlugin(const BasePlugin& descriptor) const;

	template <class T>
	const T* findPlugin(const std::string& implementationName = "") const;

	template <class T>
	const T& getPlugin(const std::string& implementationName = "");

	void addPlugin(std::unique_ptr<const BasePlugin> plugin);

protected:
	void addPlugins(const Registry& foreignRegistry, std::type_index typeIndex, const std::string& implementation = "");
	void replacePlugins(const Registry& foreignRegistry, std::type_index typeIndex, const std::string& implementation = "");

private:
#if 0
	std::string id;
	std::string name;
	std::string variant;
	std::string version;
	std::string apiVersion;
	std::string architecture;
	std::string license;
#endif
	/* Only contains plugins owned by this registry */
	std::vector<std::unique_ptr<const BasePlugin>> ownPlugins;

	/* ******************************************************** *
	 * ALL following containers store ALL plugins:           *
	 * - owned plugins (stored in plugins) and            *
	 * - foreign plugins (linked in e.g. my addRegistry(...)). *
	 * ******************************************************** */

	/* Contains meta plugins by descending order.
	 * This container is used for quick execution of method getMetaPlugins().
	 */
	std::vector<BasePlugin> metaPlugins;

	/* Contains addresses of plugins by descending order.
	 * Method "addOrReplaceRegistry(...)" uses this container of the foreign registry to insert plugins into this registry by the right order.
	 */
	std::vector<const BasePlugin*> allPlugins;

	/* Contains addresses.
	 * This container is used to make a quick check if address exists already.
	 */
	std::set<const BasePlugin*> pluginsByAddress;

	/* used by addPlugin(const Plugin& newPlugin, bool doReplace) to check if compatible plugin exists already. */
	BasePlugin* findMetaPlugin(std::type_index typeIndex, const std::string& implementation);

	/* Used by addPlugins(...) and replacePlugins(...) */
	void addOrReplacePlugins(const Registry& foreignRegistry, std::type_index typeIndex, const std::string& implementation, bool doReplace);

	/* Insert or replace plugin address and metaPlugin.
	 * To replace an potential existing plugin with the new one you have to set doReplace to true.
	 *
	 * If plugin address does not exists already
	 * and plugin type and plugin implementation does not exist already there is no different if you set doReplace to false or true.
	 *
	 * If address exists already nothing will be changed in the registry and false is returned.
	 *
	 * If plugin type and plugin implementation exist already behavior depends on doReplace.
	 * If doReplace is set to false then nothing will be changed in the object and false is returned.
	 * If doReplace is set to true then following containers (or elements in containers) will be updated:
	 * - metaPlugins (matching metaPlugin is updated to new metaPlugin)
	 * - allPlugins (matching element is updated to new address)
	 * - pluginsByAddress (old matching address is removed and new address is inserted)
	 *
	 * If insertion was successful true is returned.
	 */
	bool addPlugin(const BasePlugin& plugin, bool doReplace);
};

template <typename T, typename TPlugin>
std::unique_ptr<T> Registry::create(const std::vector<std::pair<std::string, std::string>>& settings, const std::string& implementation) {
	const TPlugin* plugin = get().findPlugin<TPlugin>(implementation);
	return plugin ? plugin->create(settings) : nullptr;
}

template <class T>
const T* Registry::findPlugin(const std::string& implementationName) const {
	static std::map<std::string, std::pair<bool, const T*>> implementations;
	static std::pair<bool, const T*> implementation{false, nullptr};

	std::pair<bool, const T*>& implementationEntry = implementationName.empty() ? implementation : implementations[implementationName];

	if(implementationEntry.first == false) {
		implementationEntry.first = true;
		implementationEntry.second = static_cast<const T*>(findBasePlugin(BasePlugin(std::type_index(typeid(T)), implementationName)));
	}

	return implementationEntry.second;
}

template <class T>
const T& Registry::getPlugin(const std::string& implementationName) {
	const T* plugin = findPlugin<T>(implementationName);

	if(plugin == nullptr) {
		if(implementationName.empty()) {
			throw std::runtime_error("no implementation available for type \"" + std::string(typeid(T).name()) + "\"");
		}
		else {
			throw std::runtime_error("no implementation available for type \"" + std::string(typeid(T).name()) + "\" and implementation \"" + implementationName + "\"");
		}
	}

	return *plugin;
}

} /* namespace plugin */
} /* namespace esl */
#if 0
#include <esl/system/stacktrace/IStacktrace.h>


namespace esl {
namespace plugin {

template <class T>
const T& Registry::getPlugin(const std::string& implementationName) {
	const T* plugin = findPlugin<T>(implementationName);

	if(plugin == nullptr) {
		if(implementationName.empty()) {
			throw system::stacktrace::IStacktrace::add(std::runtime_error("no implementation available for type \"" + std::string(T::getType()) + "\" in registry \"" + getName() + "\""));
		}
		else {
			throw system::stacktrace::IStacktrace::add(std::runtime_error("no implementation available for type \"" + std::string(T::getType()) + "\" and implementation \"" + implementationName + "\" in registry \"" + getName() + "\""));
		}
	}

	return *plugin;
}

} /* namespace plugin */
} /* namespace esl */
#endif

#endif /* ESL_PLUGIN_REGISTRY_H_ */
