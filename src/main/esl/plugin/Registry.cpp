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
typename std::aligned_storage<sizeof(Registry), alignof(Registry)>::type registryBuffer; // memory for the object;
Registry* registryPtr = nullptr;

const Registry::BasePlugins emptyBasePlugings;

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

void Registry::dump(std::ostream& ostream) const {
	ostream << "TypePlugins: " << typePlugins.size() << " entries\n";
	ostream << "-------------------------\n";
	for(const auto& typePlugin : typePlugins) {
		ostream << "    Type " << typePlugin.first.name() << ": " << typePlugin.second.size() << " entries\n";
		ostream << "    -------------------------\n";

		const BasePlugins& basePlugins = typePlugin.second;
		for(const auto& basePlugin : basePlugins) {
			ostream << "        Implementation " << basePlugin.first << ": " << (void*) basePlugin.second.get() << "\n";
		}
	}
}

const Registry::BasePlugins& Registry::getPlugins(std::type_index typeIndex) const {
	auto iter = typePlugins.find(typeIndex);
	return iter ==  typePlugins.end() ? emptyBasePlugings : iter->second;
}

const BasePlugin* Registry::findBasePlugin(const std::string& implementation, std::type_index typeIndex) const noexcept {
	auto typePluginsIter = typePlugins.find(typeIndex);
	if(typePluginsIter == typePlugins.end()) {
		return nullptr;
	}

	const BasePlugins& basePlugins = typePluginsIter->second;
	auto basePluginsIter = basePlugins.find(implementation);
	return basePluginsIter == basePlugins.end() ? nullptr : basePluginsIter->second.get();
}

const BasePlugin* Registry::findBasePlugin(std::type_index typeIndex) const noexcept {
	auto typePluginsIter = typePlugins.find(typeIndex);
	if(typePluginsIter == typePlugins.end()) {
		return nullptr;
	}

	const BasePlugins& basePlugins = typePluginsIter->second;
	auto basePluginsIter = basePlugins.begin();
	if(basePluginsIter == basePlugins.end()) {
		return nullptr;
	}

	return basePluginsIter->second.get();
}

Registry::StacktraceFactory Registry::getStacktraceFactory() {
	return get().stacktraceFactory;
}

void Registry::setStacktraceFactory(StacktraceFactory aStacktraceFactory, std::vector<std::pair<std::string, std::string>> settings) {
	get().stacktraceFactory = aStacktraceFactory;
	get().stacktraceSettings = std::move(settings);
}

const std::vector<std::pair<std::string, std::string>>& Registry::getStacktraceSettings() {
	return get().stacktraceSettings;
}

logging::Logging* Registry::getLogging() {
	return get().logging.get();
}

void Registry::setLogging(std::unique_ptr<logging::Logging> aLogging) {
	get().logging = std::move(aLogging);
}

} /* namespace plugin */
} /* namespace esl */

