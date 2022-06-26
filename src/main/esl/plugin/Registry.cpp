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

const BasePlugin* Registry::findBasePlugin(const std::string& implementation, std::type_index typeIndex) const noexcept {
	auto typePluginsIter = typePlugins.find(typeIndex);
	if(typePluginsIter == typePlugins.end()) {
		return nullptr;
	}

	const BasePlugins& basePlugins = typePluginsIter->second;
	auto basePluginsIter = implementation.empty() ? basePlugins.begin() : basePlugins.find(implementation);
	return basePluginsIter == basePlugins.end() ? nullptr : basePluginsIter->second.get();
}

} /* namespace plugin */
} /* namespace esl */
