/*
MIT License
Copyright (c) 2019, 2020 Sven Lukas

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

#include <esl/module/Module.h>

namespace esl {
namespace module {

const std::string& Module::getId() const {
	return id;
}

const std::string& Module::getName() const {
	return name;
}

const std::string& Module::getVariant() const {
	return variant;
}

const std::string& Module::getVersion() const {
	return version;
}

const std::string& Module::getApiVersion() const {
	return apiVersion;
}

const std::string& Module::getArchitecture() const {
	return architecture;
}

const std::string& Module::getLicense() const {
	return license;
}
/*
const std::vector<Descriptor>& Module::getDescriptorsProvided() const {
	return provided;
}

const std::vector<Descriptor>& Module::getDescriptorsRequired() const {
	return required;
}

const Interface* Module::getInterface(const Descriptor& descriptor) const {
	for(const auto& interface : interfaces) {
		if(descriptor.type != interface->descriptor.type) {
			continue;
		}

		if(!descriptor.implementation.empty() && descriptor.implementation != interface->descriptor.implementation) {
			continue;
		}

		if(!descriptor.apiVersion.empty() && descriptor.apiVersion != interface->descriptor.apiVersion) {
			continue;
		}

		if(!descriptor.module.empty() && descriptor.module != interface->descriptor.module) {
			continue;
		}

		return interface;
	}

	return nullptr;
}
*/

const std::vector<Interface>& Module::getDescriptorsProvided() const {
	return provided;
}

const std::vector<Interface>& Module::getDescriptorsRequired() const {
	return required;
}

const Interface* Module::getInterface(const Interface& descriptor) const {

	/* ******************** *
	 * check own interfaces *
	 * ******************** */

	for(const auto& interface : interfaces) {
		if(descriptor.type != interface->type) {
			continue;
		}

		if(!descriptor.implementation.empty() && descriptor.implementation != interface->implementation) {
			continue;
		}

		if(!descriptor.apiVersion.empty() && descriptor.apiVersion != interface->apiVersion) {
			continue;
		}

		if(!descriptor.module.empty() && descriptor.module != interface->module) {
			continue;
		}

		return interface.get();
	}

	/* ************************ *
	 * check foreign interfaces *
	 * ************************ */

	for(const auto& interface : foreignInterfaces) {
		if(descriptor.type != interface->type) {
			continue;
		}

		if(!descriptor.implementation.empty() && descriptor.implementation != interface->implementation) {
			continue;
		}

		if(!descriptor.apiVersion.empty() && descriptor.apiVersion != interface->apiVersion) {
			continue;
		}

		if(!descriptor.module.empty() && descriptor.module != interface->module) {
			continue;
		}

		return interface;
	}

	return nullptr;
}

void Module::addModule(const Module& foreignModule, const std::string& type, const std::string& implementation) {
	if(&foreignModule == this) {
		throw std::runtime_error("Cannot add module \"" + getName() + "\" to itself.");
	}
	foreignModules.insert(&foreignModule);

	for(auto& interfaceProvided : foreignModule.interfaces) {
		if(!type.empty() && type != interfaceProvided->type) {
			continue;
		}

		if(!implementation.empty() && implementation != interfaceProvided->implementation) {
			continue;
		}

		const Interface* interface = interfaceProvided.get();
		if(interface == nullptr) {
			// ERROR, interfaces must not have null pointers
			continue;
		}

		addForeignInterface(*interface);
	}
}

void Module::addInterface(std::unique_ptr<const Interface> interface) {
	if(!interface) {
		throw std::runtime_error("Cannot add empty interface to module \"" + getName() + "\".");
	}
	provided.push_back(*interface);
	interfaces.push_back(std::move(interface));
}

void Module::addForeignInterface(const Interface& interface) {
	if(foreignInterfaces.insert(&interface).second) {
		/* add interface to 'provided' only if it is does not exists already */
		provided.push_back(interface);
	}
}

} /* namespace module */
} /* namespace esl */
