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

const std::vector<Interface>& Module::getInterfaces() const {
	return provided;
}

const Interface* Module::getInterface(const Interface& descriptor) const {
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
/*
Module* Module::getModule(const std::string& module) {
	if(module == "esl") {
		return &esl::getModule();
	}
	return nullptr;
}
*/
void Module::addModule(const Module& foreignModule, const std::string& type, const std::string& implementation) {
	addOrReplaceModule(foreignModule, type, implementation, false);
}

void Module::replaceModule(const Module& foreignModule, const std::string& type, const std::string& implementation) {
	addOrReplaceModule(foreignModule, type, implementation, true);
}

void Module::addInterface(std::unique_ptr<const Interface> interface) {
	if(!interface) {
		throw std::runtime_error("Cannot add empty interface to module \"" + getName() + "\".");
	}

	if(addInterfaceIntern(*interface.get())) {
		mainInterfaces.push_back(std::move(interface));
	}
}

Interface* Module::getProvidedInterface(const std::string& type, const std::string& implementation) {
	for(auto& providedInterface : provided) {
		if(type != providedInterface.type) {
			continue;
		}

		if(implementation != providedInterface.implementation) {
			continue;
		}

		return &providedInterface;
	}
	return nullptr;
}

void Module::addOrReplaceModule(const Module& foreignModule, const std::string& type, const std::string& implementation, bool replace) {
	if(&foreignModule == this) {
		throw std::runtime_error("Cannot add module \"" + getName() + "\" to itself.");
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

		if(replace) {
			replaceInterfaceIntern(*foreignInterface);
		}
		else {
			addInterfaceIntern(*foreignInterface);
		}
	}
}

bool Module::addInterfaceIntern(const Interface& newInterface) {
	if(allInterfacesByAddress.insert(&newInterface).second == false) {
		return false;
	}

	if(getProvidedInterface(newInterface.type, newInterface.implementation)) {
		return false;
	}

	provided.push_back(newInterface);
	allInterfaces.push_back(&newInterface);

	return true;
}

void Module::replaceInterfaceIntern(const Interface& newInterface) {
	if(allInterfacesByAddress.insert(&newInterface).second == false) {
		return;
	}

	Interface* providedInterface = getProvidedInterface(newInterface.type, newInterface.implementation);
	if(providedInterface) {
		*providedInterface = newInterface;

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

			allInterfacesByAddress.erase(interface);
			interface = &newInterface;
		}
	}
	else {
		provided.push_back(newInterface);
		allInterfaces.push_back(&newInterface);
	}

}

} /* namespace module */
} /* namespace esl */
