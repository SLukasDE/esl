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

#include <esl/plugin/Registry.h>

#include <utility>

namespace esl {
inline namespace v1_6 {
namespace plugin {

namespace {
std::unique_ptr<Registry> registryUnique;
Registry* registryPtr = nullptr;
const Registry::BasePlugins emptyBasePlugings;
}  /* anonymous namespace */

Registry::~Registry() {
	for(auto& object : objects) {
		// The monitoring::Logging is the last object to be deleted, because every Logger has a pointer to this object.
		if(object.first == typeid(monitoring::Logging)) {
			continue;
		}
		object.second.reset();
	}
	objects.clear();

	if(registryPtr == this) {
		registryPtr = nullptr;
	}
}

Registry& Registry::get() {
	if(registryPtr == nullptr) {
		registryUnique.reset(new Registry);
		registryPtr = registryUnique.get();
	}

	return *registryPtr;
}

void Registry::set(Registry& registry) {
	registryPtr = &registry;
}

void Registry::cleanup() {
	if(registryPtr == registryUnique.get()) {
		registryPtr = nullptr;
	}
	registryUnique.reset();
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

void Registry::loadPlugin(const std::string& path, const char* data) {
	loadPlugin(std::unique_ptr<Library>(new Library(path)), data);
}

void Registry::loadPlugin(std::unique_ptr<Library> library, const char* data) {
	library->install(*this, data);
	libraries.push_back(std::move(library));
}
} /* namespace plugin */
} /* inline namespace v1_6 */
} /* namespace esl */

