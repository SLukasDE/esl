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

#include <esl/plugin/Registry.h>

#include <new>         // placement new
#include <type_traits> // aligned_storage
#include <utility>

namespace esl {
namespace plugin {

namespace {
#if 0
class InternalRegistry : public Registry {
public:
	InternalRegistry();
};

InternalRegistry::InternalRegistry()
{
	Registry::initialize(*this);
}
#endif

typename std::aligned_storage<sizeof(Registry), alignof(Registry)>::type registryBuffer; // memory for the object;
Registry* registryPtr = nullptr;

}  /* anonymous namespace */


Registry& Registry::get() {
	if(registryPtr == nullptr) {
		/* ***************** *
		 * initialize module *
		 * ***************** */

		registryPtr = reinterpret_cast<Registry*> (&registryBuffer);
		new (registryPtr) Registry; // placement new
	}

	return *registryPtr;
}

void Registry::set(Registry& registry) {
	registryPtr = &registry;
}
#if 0
const std::string& Registry::getId() const {
	return id;
}

const std::string& Registry::getName() const {
	return name;
}

const std::string& Registry::getVariant() const {
	return variant;
}

const std::string& Registry::getVersion() const {
	return version;
}

const std::string& Registry::getApiVersion() const {
	return apiVersion;
}

const std::string& Registry::getArchitecture() const {
	return architecture;
}

const std::string& Registry::getLicense() const {
	return license;
}
#endif
const std::vector<BasePlugin>& Registry::getMetaPlugins() const {
	return metaPlugins;
}

const BasePlugin* Registry::findBasePlugin(const BasePlugin& descriptor) const {
	for(auto plugin : allPlugins) {
		if(!plugin) {
			continue;
		}

		if(descriptor.typeIndex != plugin->typeIndex) {
			continue;
		}

		if(!descriptor.implementation.empty() && descriptor.implementation != plugin->implementation) {
			continue;
		}

		return plugin;
	}

	return nullptr;
}

void Registry::addPlugin(std::unique_ptr<const BasePlugin> plugin) {
	if(!plugin) {
		throw std::runtime_error("Cannot add empty plugin.");
	}

	if(addPlugin(*plugin.get(), false)) {
		ownPlugins.push_back(std::move(plugin));
	}
}

void Registry::addPlugins(const Registry& foreignRegistry, std::type_index typeIndex, const std::string& implementation) {
	addOrReplacePlugins(foreignRegistry, typeIndex, implementation, false);
}

void Registry::replacePlugins(const Registry& foreignRegistry, std::type_index typeIndex, const std::string& implementation) {
	addOrReplacePlugins(foreignRegistry, typeIndex, implementation, true);
}

BasePlugin* Registry::findMetaPlugin(std::type_index typeIndex, const std::string& implementation) {
	for(auto& metaPlugin : metaPlugins) {
		if(typeIndex != metaPlugin.typeIndex) {
			continue;
		}

		if(implementation != metaPlugin.implementation) {
			continue;
		}

		return &metaPlugin;
	}
	return nullptr;
}

void Registry::addOrReplacePlugins(const Registry& foreignRegistry, std::type_index typeIndex, const std::string& implementation, bool doReplace) {
	if(&foreignRegistry == this) {
		return;
	}

	for(auto foreignPlugin : foreignRegistry.allPlugins) {
		if(foreignPlugin == nullptr) {
			// ERROR, plugins must not have null pointers
			continue;
		}

		if(typeIndex != foreignPlugin->typeIndex) {
			continue;
		}

		if(!implementation.empty() && implementation != foreignPlugin->implementation) {
			continue;
		}

		addPlugin(*foreignPlugin, doReplace);
	}
}

bool Registry::addPlugin(const BasePlugin& newPlugin, bool doReplace) {
	/* Check if address exists already. */
	if(pluginsByAddress.find(&newPlugin) != pluginsByAddress.end()) {
		/* Address exist already. */
		return false;
	}

	/* Check if an plugin with same type and implementation exists already. */
	BasePlugin* metaPlugin = findMetaPlugin(newPlugin.typeIndex, newPlugin.implementation);
	if(metaPlugin) {
		/* Type and implementation exists already.
		 * Check if replace is forbidden. */
		if(doReplace == false) {
			return false;
		}

		/* Replace meta plugin. */
		*metaPlugin = newPlugin;

		for(auto& plugin : allPlugins) {
			if(!plugin) {
				continue;
			}

			if(plugin->typeIndex != newPlugin.typeIndex) {
				continue;
			}

			if(!plugin->implementation.empty() && plugin->implementation != newPlugin.implementation) {
				continue;
			}

			/* Replace plugin address. */
			pluginsByAddress.erase(plugin);
			pluginsByAddress.insert(&newPlugin);
			plugin = &newPlugin;
		}
	}
	else {
		/* Insert meta plugin. */
		metaPlugins.push_back(newPlugin);

		/* Insert plugin address. */
		pluginsByAddress.insert(&newPlugin);
		allPlugins.push_back(&newPlugin);
	}

	return true;
}

} /* namespace plugin */
} /* namespace esl */
