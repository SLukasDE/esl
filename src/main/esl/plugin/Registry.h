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
	static Registry& get();
	static void set(Registry& registry);

	void dump() const;

	template<typename Interface>
	std::unique_ptr<Interface> create(const std::string& implementation, const std::vector<std::pair<std::string, std::string>>& settings);

	template <class Interface>
	const Plugin<Interface>* findPlugin(const std::string& implementation) const noexcept;

	template <class Interface>
	const Plugin<Interface>& getPlugin(const std::string& implementation) const;

	template <class Interface>
	void addPlugin(const std::string& implementation, std::unique_ptr<Interface> (*create)(const std::vector<std::pair<std::string, std::string>>&));

	template <class Interface>
	void copyPlugin(const std::string& implementationSource, const std::string& implementationDestination);

private:
	using BasePlugins = std::map<std::string, std::unique_ptr<const BasePlugin>>;
	using TypePlugins = std::map<std::type_index, BasePlugins>;

	TypePlugins typePlugins;

	const BasePlugin* findBasePlugin(const std::string& implementation, std::type_index typeIndex) const noexcept;
};


template <class Interface>
const Plugin<Interface>* Registry::findPlugin(const std::string& implementation) const noexcept {
	return static_cast<const Plugin<Interface>*>(findBasePlugin(implementation, typeid(Interface)));
}

template <class Interface>
const Plugin<Interface>& Registry::getPlugin(const std::string& implementation) const {
	const Plugin<Interface>* plugin = findPlugin<Interface>(implementation);

	if(plugin == nullptr) {
		if(implementation.empty()) {
			throw std::runtime_error("no implementation available for type \"" + std::string(typeid(Interface).name()) + "\"");
		}
		else {
			throw std::runtime_error("no implementation available for type \"" + std::string(typeid(Interface).name()) + "\" and implementation \"" + implementation + "\"");
		}
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

template <typename Interface>
std::unique_ptr<Interface> Registry::create(const std::string& implementation, const std::vector<std::pair<std::string, std::string>>& settings) {
	const Plugin<Interface>* plugin = findPlugin<Interface>(implementation);
	return plugin ? plugin->create(settings) : nullptr;
}

} /* namespace plugin */
} /* namespace esl */

#endif /* ESL_PLUGIN_REGISTRY_H_ */
