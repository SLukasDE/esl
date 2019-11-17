/*
MIT License
Copyright (c) 2019 Sven Lukas

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

#include <esl/bootstrap/Module.h>

namespace esl {
namespace bootstrap {

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

const Interface& Module::getInterfacesProvided() const {
	return interfacesProvided;
}

const Interface* Module::getInterface(const std::string& id, const std::string& apiVersion) const {
	for(const Interface* interfacePtr = &getInterfacesProvided(); interfacePtr != nullptr; interfacePtr = interfacePtr->next) {
		if(interfacePtr->id == id && interfacePtr->apiVersion == apiVersion) {
			return interfacePtr;
		}
	}
	return nullptr;
}

} /* namespace bootstrap */
} /* namespace esl */
