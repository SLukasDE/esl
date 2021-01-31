/*
MIT License
Copyright (c) 2019-2021 Sven Lukas

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
#include <esl/Module.h>
#include <utility>

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

const std::vector<Interface>& Module::getMetaInterfaces() const {
	return metaInterfaces;
}

const Interface* Module::findInterface(const Interface& descriptor) const {
	for(auto interface : allInterfaces) {
		if(!interface) {
			continue;
		}

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

void Module::addInterfaces(const Module& foreignModule, const std::string& type, const std::string& implementation) {
	addOrReplaceInterfaces(foreignModule, type, implementation, false);
}

void Module::replaceInterfaces(const Module& foreignModule, const std::string& type, const std::string& implementation) {
	addOrReplaceInterfaces(foreignModule, type, implementation, true);
}

void Module::addInterface(std::unique_ptr<const Interface> interface) {
	if(!interface) {
		throw std::runtime_error("Cannot add empty interface to module \"" + getName() + "\".");
	}

	if(addInterface(*interface.get(), false)) {
		ownInterfaces.push_back(std::move(interface));
	}
}

Interface* Module::findMetaInterface(const std::string& type, const std::string& implementation) {
	for(auto& metaInterface : metaInterfaces) {
		if(type != metaInterface.type) {
			continue;
		}

		if(implementation != metaInterface.implementation) {
			continue;
		}

		return &metaInterface;
	}
	return nullptr;
}

void Module::addOrReplaceInterfaces(const Module& foreignModule, const std::string& type, const std::string& implementation, bool doReplace) {
	if(&foreignModule == this) {
		return;
	}

	for(auto foreignInterface : foreignModule.allInterfaces) {
		if(foreignInterface == nullptr) {
			// ERROR, interfaces must not have null pointers
			continue;
		}

		if(!type.empty() && type != foreignInterface->type) {
			continue;
		}

		if(!implementation.empty() && implementation != foreignInterface->implementation) {
			continue;
		}

		addInterface(*foreignInterface, doReplace);
	}
}

bool Module::addInterface(const Interface& newInterface, bool doReplace) {
	/* Check if address exists already. */
	if(interfacesByAddress.find(&newInterface) != interfacesByAddress.end()) {
		/* Address exist already. */
		return false;
	}

	/* Check if an interface with same type and implementation exists already. */
	Interface* metaInterface = findMetaInterface(newInterface.type, newInterface.implementation);
	if(metaInterface) {
		/* Type and implementation exists already.
		 * Check if replace is forbidden. */
		if(doReplace == false) {
			return false;
		}

		/* Replace meta interface. */
		*metaInterface = newInterface;

		for(auto& interface : allInterfaces) {
			if(!interface) {
				continue;
			}

			if(interface->type != newInterface.type) {
				continue;
			}

			if(!interface->implementation.empty() && interface->implementation != newInterface.implementation) {
				continue;
			}

			if(!interface->apiVersion.empty() && interface->apiVersion != newInterface.apiVersion) {
				continue;
			}

			if(!interface->module.empty() && interface->module != newInterface.module) {
				continue;
			}

			/* Replace interface address. */
			interfacesByAddress.erase(interface);
			interfacesByAddress.insert(&newInterface);
			interface = &newInterface;
		}
	}
	else {
		/* Insert meta interface. */
		metaInterfaces.push_back(newInterface);

		/* Insert interface address. */
		interfacesByAddress.insert(&newInterface);
		allInterfaces.push_back(&newInterface);
	}

	return true;
}

} /* namespace module */
} /* namespace esl */
