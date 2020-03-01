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

#ifndef ESL_MODULE_MODULE_H_
#define ESL_MODULE_MODULE_H_

#include <esl/module/Interface.h>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>

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
namespace module {

class Module {
	friend class Library;
public:
	Module() = default;
	virtual ~Module() = default;

	const std::string& getId() const;
	const std::string& getName() const;
	const std::string& getVariant() const;
	const std::string& getVersion() const;
	const std::string& getApiVersion() const;
	const std::string& getArchitecture() const;
	const std::string& getLicense() const;

	static inline void initialize(Module& module) {
		module.id = QUOTE(TRANSFORMER_ARTEFACT_ID);
		module.name = QUOTE(TRANSFORMER_ARTEFACT_NAME);
		module.variant = QUOTE(TRANSFORMER_ARTEFACT_VARIANT);
		module.version = QUOTE(TRANSFORMER_ARTEFACT_VERSION);
		module.apiVersion = QUOTE(TRANSFORMER_ARTEFACT_API_VERSION);
		module.architecture = QUOTE(TRANSFORMER_ARTEFACT_ARCHITECTURE);
		module.license = QUOTE(TRANSFORMER_ARTEFACT_LICENSE);
	}

	const std::vector<Interface>& getInterfaces() const;
	const Interface* getInterface(const Interface& descriptor) const;

	template <class T>
	const T* getInterfacePointer(const std::string& implementationName = "");

	template <class T>
	const T& getInterface(const std::string& implementationName = "");

	virtual Module* getModule(const std::string& module);
	void addModule(const Module& foreignModule, const std::string& type = "", const std::string& implementation = "");
	void replaceModule(const Module& foreignModule, const std::string& type = "", const std::string& implementation = "");

protected:
	void addInterface(std::unique_ptr<const Interface> interface);

private:
	/* contains descriptors of all interfaces provided by this module, independent if it is a mainInterfaces or external added interface.
	 * This container is used for method getInterfaces()
	 */
	std::vector<Interface> provided;

	/* contains only main interfaces added by addMainInterface() */
	std::vector<std::unique_ptr<const Interface>> mainInterfaces;

	/* contains all interfaces added by addInterface() [e.g. indirectly by addMainInterface()] */
	std::set<const Interface*> allInterfacesByAddress;
	std::vector<const Interface*> allInterfaces;

	std::string id;
	std::string name;
	std::string variant;
	std::string version;
	std::string apiVersion;
	std::string architecture;
	std::string license;

	Interface* getProvidedInterface(const std::string& type, const std::string& implementation);
	void addOrReplaceModule(const Module& foreignModule, const std::string& type, const std::string& implementation, bool replace);
	bool addInterfaceIntern(const Interface& interface);
	void replaceInterfaceIntern(const Interface& interface);
};

template <class T>
const T* Module::getInterfacePointer(const std::string& implementationName) {
	static std::map<std::string, std::pair<bool, const T*>> implementations;
	static std::pair<bool, const T*> implementation{false, nullptr};

	std::pair<bool, const T*>& implementationEntry = implementationName.empty() ? implementation : implementations[implementationName];

	if(implementationEntry.first == false) {
		implementationEntry.first = true;
		implementationEntry.second = static_cast<const T*>(getInterface(Interface("", T::getType(), implementationName, T::getApiVersion())));
	}

	return implementationEntry.second;
}

template <class T>
const T& Module::getInterface(const std::string& implementationName) {
	const T* interface = getInterfacePointer<T>(implementationName);

	if(interface == nullptr) {
		if(implementationName.empty()) {
			throw std::runtime_error("no implementation available for type \"" + std::string(T::getType()) + "\" in module \"" + getName() + "\"");
		}
		else {
			throw std::runtime_error("no implementation available for type \"" + std::string(T::getType()) + "\" and implementation \"" + implementationName + "\" in module \"" + getName() + "\"");
		}
	}

	return *interface;
}

} /* namespace module */
} /* namespace esl */

#endif /* ESL_MODULE_MODULE_H_ */
